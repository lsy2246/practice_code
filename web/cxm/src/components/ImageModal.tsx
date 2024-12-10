import { useEffect } from 'react';
import './ImageModal.css';

interface ImageModalProps {
  image: string;
  onClose: () => void;
}

export const ImageModal = ({ image, onClose }: ImageModalProps) => {
  useEffect(() => {
    const handleEsc = (e: KeyboardEvent) => {
      if (e.key === 'Escape') {
        onClose();
      }
    };
    window.addEventListener('keydown', handleEsc);
    return () => window.removeEventListener('keydown', handleEsc);
  }, [onClose]);

  return (
    <div className="modal-overlay" onClick={onClose}>
      <div className="modal-content" onClick={e => e.stopPropagation()}>
        <button className="modal-close" onClick={onClose}>×</button>
        <img src={image} alt="" className="modal-image" />
      </div>
    </div>
  );
}; 