"use strict";
/*
 * ATTENTION: The "eval" devtool has been used (maybe by default in mode: "development").
 * This devtool is neither made for production nor for readable output files.
 * It uses "eval()" calls to create a separate source file in the browser devtools.
 * If you are trying to read the output file, select a different devtool (https://webpack.js.org/configuration/devtool/)
 * or disable the default devtool with "devtool: false".
 * If you are looking for production-ready output files, see mode: "production" (https://webpack.js.org/configuration/mode/).
 */
(self["webpackChunkwasm"] = self["webpackChunkwasm"] || []).push([["pkg_wasm_js"],{

/***/ "./pkg/wasm.js":
/*!*********************!*\
  !*** ./pkg/wasm.js ***!
  \*********************/
/***/ ((__webpack_module__, __webpack_exports__, __webpack_require__) => {

eval("__webpack_require__.a(__webpack_module__, async (__webpack_handle_async_dependencies__, __webpack_async_result__) => { try {\n__webpack_require__.r(__webpack_exports__);\n/* harmony export */ __webpack_require__.d(__webpack_exports__, {\n/* harmony export */   __wbg_alert_e63a4c41bbd7a3e9: () => (/* reexport safe */ _wasm_bg_js__WEBPACK_IMPORTED_MODULE_0__.__wbg_alert_e63a4c41bbd7a3e9),\n/* harmony export */   __wbg_set_wasm: () => (/* reexport safe */ _wasm_bg_js__WEBPACK_IMPORTED_MODULE_0__.__wbg_set_wasm),\n/* harmony export */   greet: () => (/* reexport safe */ _wasm_bg_js__WEBPACK_IMPORTED_MODULE_0__.greet)\n/* harmony export */ });\n/* harmony import */ var _wasm_bg_wasm__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! ./wasm_bg.wasm */ \"./pkg/wasm_bg.wasm\");\n/* harmony import */ var _wasm_bg_js__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./wasm_bg.js */ \"./pkg/wasm_bg.js\");\nvar __webpack_async_dependencies__ = __webpack_handle_async_dependencies__([_wasm_bg_wasm__WEBPACK_IMPORTED_MODULE_1__]);\n_wasm_bg_wasm__WEBPACK_IMPORTED_MODULE_1__ = (__webpack_async_dependencies__.then ? (await __webpack_async_dependencies__)() : __webpack_async_dependencies__)[0];\n\n\n\n(0,_wasm_bg_js__WEBPACK_IMPORTED_MODULE_0__.__wbg_set_wasm)(_wasm_bg_wasm__WEBPACK_IMPORTED_MODULE_1__);\n__webpack_async_result__();\n} catch(e) { __webpack_async_result__(e); } });\n\n//# sourceURL=webpack://wasm/./pkg/wasm.js?");

/***/ }),

/***/ "./pkg/wasm_bg.js":
/*!************************!*\
  !*** ./pkg/wasm_bg.js ***!
  \************************/
/***/ ((__unused_webpack___webpack_module__, __webpack_exports__, __webpack_require__) => {

eval("__webpack_require__.r(__webpack_exports__);\n/* harmony export */ __webpack_require__.d(__webpack_exports__, {\n/* harmony export */   __wbg_alert_e63a4c41bbd7a3e9: () => (/* binding */ __wbg_alert_e63a4c41bbd7a3e9),\n/* harmony export */   __wbg_set_wasm: () => (/* binding */ __wbg_set_wasm),\n/* harmony export */   greet: () => (/* binding */ greet)\n/* harmony export */ });\nlet wasm;\nfunction __wbg_set_wasm(val) {\n    wasm = val;\n}\n\n\nconst lTextDecoder = typeof TextDecoder === 'undefined' ? (0, module.require)('util').TextDecoder : TextDecoder;\n\nlet cachedTextDecoder = new lTextDecoder('utf-8', { ignoreBOM: true, fatal: true });\n\ncachedTextDecoder.decode();\n\nlet cachedUint8ArrayMemory0 = null;\n\nfunction getUint8ArrayMemory0() {\n    if (cachedUint8ArrayMemory0 === null || cachedUint8ArrayMemory0.byteLength === 0) {\n        cachedUint8ArrayMemory0 = new Uint8Array(wasm.memory.buffer);\n    }\n    return cachedUint8ArrayMemory0;\n}\n\nfunction getStringFromWasm0(ptr, len) {\n    ptr = ptr >>> 0;\n    return cachedTextDecoder.decode(getUint8ArrayMemory0().subarray(ptr, ptr + len));\n}\n\nfunction greet() {\n    wasm.greet();\n}\n\nfunction __wbg_alert_e63a4c41bbd7a3e9(arg0, arg1) {\n    alert(getStringFromWasm0(arg0, arg1));\n};\n\n\n\n//# sourceURL=webpack://wasm/./pkg/wasm_bg.js?");

/***/ }),

/***/ "./pkg/wasm_bg.wasm":
/*!**************************!*\
  !*** ./pkg/wasm_bg.wasm ***!
  \**************************/
/***/ ((module, exports, __webpack_require__) => {

eval("/* harmony import */ var WEBPACK_IMPORTED_MODULE_0 = __webpack_require__(/*! ./wasm_bg.js */ \"./pkg/wasm_bg.js\");\nmodule.exports = __webpack_require__.v(exports, module.id, \"bd225cef621f4330ec1f\", {\n\t\"./wasm_bg.js\": {\n\t\t\"__wbg_alert_e63a4c41bbd7a3e9\": WEBPACK_IMPORTED_MODULE_0.__wbg_alert_e63a4c41bbd7a3e9\n\t}\n});\n\n//# sourceURL=webpack://wasm/./pkg/wasm_bg.wasm?");

/***/ })

}]);