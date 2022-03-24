"use strict";
function OpenProject() {
    const file = api.showOpenFileDialog();
    const filePath = file.__dirname;
    console.log("Done");
    if (file != null) {
        localStorage.setItem('path', filePath);
        location.href = './views/projectOpen.html';
    }
}
(() => {
    var _a, _b;
    (_a = document.querySelector('#btn-open-project')) === null || _a === void 0 ? void 0 : _a.addEventListener('click', () => {
        OpenProject();
    }),
        (_b = document.querySelector('#btn-new-project')) === null || _b === void 0 ? void 0 : _b.addEventListener('click', () => {
            location.href = './views/projectNew.html';
        });
})();
