// src/lib.rs
use wasm_bindgen::prelude::*;
use ttf_parser::{Face, GlyphId, OutlineBuilder};
use svg::Document;
use svg::node::element::{Path, Text, SVG};
use std::collections::HashMap;
use console_error_panic_hook;

struct PathBuilder {
    path_data: String,
    x_offset: f32,
    y_offset: f32,
    scale: f32,
    path_length: f32,
    current_x: f32,
    current_y: f32,
    min_x: f32,
    max_x: f32,
    min_y: f32,
    max_y: f32,
}

impl PathBuilder {
    fn new(x_offset: f32, y_offset: f32, scale: f32) -> Self {
        PathBuilder {
            path_data: String::new(),
            x_offset,
            y_offset,
            scale,
            path_length: 0.0,
            current_x: 0.0,
            current_y: 0.0,
            min_x: f32::MAX,
            max_x: f32::MIN,
            min_y: f32::MAX,
            max_y: f32::MIN,
        }
    }

    fn calculate_distance(&self, x1: f32, y1: f32, x2: f32, y2: f32) -> f32 {
        let dx = x2 - x1;
        let dy = y2 - y1;
        (dx * dx + dy * dy).sqrt()
    }

    fn calculate_curve_length(&mut self, x1: f32, y1: f32, x2: f32, y2: f32, x: f32, y: f32) -> f32 {
        let segments = 10;
        let mut length = 0.0;
        let mut prev_x = self.current_x;
        let mut prev_y = self.current_y;

        for i in 1..=segments {
            let t = i as f32 / segments as f32;
            let t2 = t * t;
            let t3 = t2 * t;
            let mt = 1.0 - t;
            let mt2 = mt * mt;
            let mt3 = mt2 * mt;

            let x = mt3 * self.current_x + 3.0 * mt2 * t * x1 + 3.0 * mt * t2 * x2 + t3 * x;
            let y = mt3 * self.current_y + 3.0 * mt2 * t * y1 + 3.0 * mt * t2 * y2 + t3 * y;

            length += self.calculate_distance(prev_x, prev_y, x, y);
            prev_x = x;
            prev_y = y;
        }

        length
    }

    fn update_bounds(&mut self, x: f32, y: f32) {
        self.min_x = self.min_x.min(x);
        self.max_x = self.max_x.max(x);
        self.min_y = self.min_y.min(y);
        self.max_y = self.max_y.max(y);
    }
}

impl OutlineBuilder for PathBuilder {
    fn move_to(&mut self, x: f32, y: f32) {
        let scaled_x = x * self.scale + self.x_offset;
        let scaled_y = self.y_offset - y * self.scale;
        self.update_bounds(scaled_x, scaled_y);
        self.path_data.push_str(&format!("M {} {} ", scaled_x, scaled_y));
        self.current_x = scaled_x;
        self.current_y = scaled_y;
    }

    fn line_to(&mut self, x: f32, y: f32) {
        let scaled_x = x * self.scale + self.x_offset;
        let scaled_y = self.y_offset - y * self.scale;
        self.update_bounds(scaled_x, scaled_y);
        let length = self.calculate_distance(self.current_x, self.current_y, scaled_x, scaled_y);
        self.path_length += length;
        self.path_data.push_str(&format!("L {} {} ", scaled_x, scaled_y));
        self.current_x = scaled_x;
        self.current_y = scaled_y;
    }

    fn quad_to(&mut self, x1: f32, y1: f32, x: f32, y: f32) {
        let scaled_x1 = x1 * self.scale + self.x_offset;
        let scaled_y1 = self.y_offset - y1 * self.scale;
        let scaled_x = x * self.scale + self.x_offset;
        let scaled_y = self.y_offset - y * self.scale;
        self.update_bounds(scaled_x1, scaled_y1);
        self.update_bounds(scaled_x, scaled_y);
        
        let length = self.calculate_distance(self.current_x, self.current_y, scaled_x1, scaled_y1) +
                    self.calculate_distance(scaled_x1, scaled_y1, scaled_x, scaled_y);
        self.path_length += length;

        self.path_data.push_str(&format!("Q {} {} {} {} ", scaled_x1, scaled_y1, scaled_x, scaled_y));
        self.current_x = scaled_x;
        self.current_y = scaled_y;
    }

    fn curve_to(&mut self, x1: f32, y1: f32, x2: f32, y2: f32, x: f32, y: f32) {
        let scaled_x1 = x1 * self.scale + self.x_offset;
        let scaled_y1 = self.y_offset - y1 * self.scale;
        let scaled_x2 = x2 * self.scale + self.x_offset;
        let scaled_y2 = self.y_offset - y2 * self.scale;
        let scaled_x = x * self.scale + self.x_offset;
        let scaled_y = self.y_offset - y * self.scale;
        self.update_bounds(scaled_x1, scaled_y1);
        self.update_bounds(scaled_x2, scaled_y2);
        self.update_bounds(scaled_x, scaled_y);

        let length = self.calculate_curve_length(scaled_x1, scaled_y1, scaled_x2, scaled_y2, scaled_x, scaled_y);
        self.path_length += length;

        self.path_data.push_str(&format!("C {} {} {} {} {} {} ", 
            scaled_x1, scaled_y1, scaled_x2, scaled_y2, scaled_x, scaled_y));
        self.current_x = scaled_x;
        self.current_y = scaled_y;
    }

    fn close(&mut self) {
        if self.current_x != self.x_offset || self.current_y != self.y_offset {
            let length = self.calculate_distance(self.current_x, self.current_y, self.x_offset, self.y_offset);
            self.path_length += length;
        }
        self.path_data.push('Z');
    }
}

#[wasm_bindgen]
pub struct FontHandler {
    font_data: Vec<u8>,
    units_per_em: f32,
    ascender: f32,
    descender: f32,
}

#[wasm_bindgen]
impl FontHandler {
    #[wasm_bindgen(constructor)]
    pub fn new(font_data: &[u8]) -> Result<FontHandler, JsValue> {
        let font_data = font_data.to_vec(); // Own the data
        let face = Face::parse(&font_data, 0)
            .map_err(|e| JsValue::from_str(&format!("Failed to parse font: {:?}", e)))?;
        
        Ok(FontHandler {
            units_per_em: face.units_per_em() as f32,
            ascender: face.ascender() as f32,
            descender: face.descender() as f32,
            font_data,
        })
    }

    #[wasm_bindgen]
    pub fn generate_svg(&self, text: &str, font_size: f32) -> Result<String, JsValue> {
        let face = Face::parse(&self.font_data, 0)
            .map_err(|e| JsValue::from_str(&format!("Failed to parse font: {:?}", e)))?;
        
        let scale_factor = font_size / self.units_per_em;
        let baseline = font_size * 1.2;
        
        let mut x_position = 0.0;
        let mut paths = Vec::new();
        let mut total_width = 0.0;

        let mut min_x = f32::MAX;
        let mut max_x = f32::MIN;
        let mut min_y = f32::MAX;
        let mut max_y = f32::MIN;

        for c in text.chars() {
            if let Some(glyph_id) = face.glyph_index(c) {
                if let Some(advance) = face.glyph_hor_advance(glyph_id) {
                    total_width += advance as f32 * scale_factor;
                }
            }
        }

        let margin = font_size * 0.5;
        let total_width = total_width + margin * 2.0;
        x_position = margin;

        for c in text.chars() {
            if let Some(glyph_id) = face.glyph_index(c) {
                if let Some(advance) = face.glyph_hor_advance(glyph_id) {
                    let mut builder = PathBuilder::new(x_position, baseline, scale_factor);
                    
                    if let Some(_) = face.outline_glyph(glyph_id, &mut builder) {
                        if !builder.path_data.is_empty() {
                            min_x = min_x.min(builder.min_x);
                            max_x = max_x.max(builder.max_x);
                            min_y = min_y.min(builder.min_y);
                            max_y = max_y.max(builder.max_y);
                            
                            paths.push(Path::new()
                                .set("d", builder.path_data)
                                .set("fill", "currentColor"));
                        }
                    }
                    
                    x_position += advance as f32 * scale_factor;
                }
            }
        }

        let padding = font_size * 0.1;
        let view_box_x = min_x - padding;
        let view_box_y = min_y - padding;
        let view_box_width = (max_x - min_x) + padding * 2.0;
        let view_box_height = (max_y - min_y) + padding * 2.0;

        let mut document = Document::new()
            .set("viewBox", (view_box_x, view_box_y, view_box_width, view_box_height))
            .set("class", "animated-text")
            .set("preserveAspectRatio", "xMidYMid meet")
            .set("style", "width: 100%; height: 100%;");

        for path in paths {
            document = document.add(path);
        }

        Ok(document.to_string())
    }
}

#[wasm_bindgen]
pub fn init_panic_hook() {
    console_error_panic_hook::set_once();
}