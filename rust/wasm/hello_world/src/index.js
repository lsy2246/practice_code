const js = import("../pkg/wasm");

js.then((js) => {
    js.greet();
})