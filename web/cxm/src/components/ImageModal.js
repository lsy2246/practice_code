import { jsx as _jsx, jsxs as _jsxs } from "react/jsx-runtime";
import { useEffect } from 'react';
import './ImageModal.css';
export const ImageModal = ({ image, onClose }) => {
    useEffect(() => {
        const handleEsc = (e) => {
            if (e.key === 'Escape') {
                onClose();
            }
        };
        window.addEventListener('keydown', handleEsc);
        return () => window.removeEventListener('keydown', handleEsc);
    }, [onClose]);
    return (_jsx("div", { className: "modal-overlay", onClick: onClose, children: _jsxs("div", { className: "modal-content", onClick: e => e.stopPropagation(), children: [_jsx("button", { className: "modal-close", onClick: onClose, children: "\u00D7" }), _jsx("img", { src: image, alt: "", className: "modal-image" })] }) }));
};
