"use strict";
//@ts-expect-error
document.getElementById('hi').textContent = localStorage.getItem('path');
(() => {
    var _a;
    (_a = document.querySelector('#CompileButton')) === null || _a === void 0 ? void 0 : _a.addEventListener('click', () => {
        api.OpenCmd(localStorage.getItem('path'));
    });
})();
