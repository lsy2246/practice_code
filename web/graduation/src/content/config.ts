import { defineCollection, z } from 'astro:content';

// 景点集合的Schema
const attractionsCollection = defineCollection({
  type: 'content',
  schema: z.object({
    title: z.string(),
    description: z.string(),
    featured: z.boolean().default(false),
    image: z.string().optional(),
    city: z.string().optional(),
    tags: z.array(z.string()).default([]),
    pubDate: z.date().optional(),
  }),
});

// 文化集合的Schema
const cultureCollection = defineCollection({
  type: 'content',
  schema: z.object({
    title: z.string(),
    description: z.string(),
    category: z.string(),
    featured: z.boolean().default(false),
    image: z.string().optional(),
    city: z.string().optional(),
    tags: z.array(z.string()).default([]),
    pubDate: z.date().optional(),
  }),
});

// 美食集合的Schema
const cuisineCollection = defineCollection({
  type: 'content',
  schema: z.object({
    title: z.string(),
    description: z.string(),
    category: z.string(),
    featured: z.boolean().default(false),
    image: z.string().optional(),
    city: z.string().optional(),
    ingredients: z.array(z.string()).default([]),
    taste: z.string().optional(),
    cookTime: z.string().optional(),
    difficulty: z.string().optional(),
    tags: z.array(z.string()).default([]),
    pubDate: z.date().optional(),
  }),
});

// 旅游攻略集合的Schema
const travelCollection = defineCollection({
  type: 'content',
  schema: z.object({
    title: z.string(),
    description: z.string(),
    season: z.enum(['春季', '夏季', '秋季', '冬季']).optional(),
    type: z.string(),
    featured: z.boolean().default(false),
    image: z.string().optional(),
    city: z.string().optional(),
    days: z.number().optional(),
    difficulty: z.enum(['简单', '中等', '困难']).optional(),
    tags: z.array(z.string()).default([]),
    pubDate: z.date().optional(),
  }),
});

// 导出集合配置
export const collections = {
  'attractions': attractionsCollection,
  'culture': cultureCollection,
  'cuisine': cuisineCollection,
  'travel': travelCollection,
}; 
