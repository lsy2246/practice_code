import { StrictMode } from 'react'
import { createRoot } from 'react-dom/client'
import WasmComponent from './App.tsx'

createRoot(document.getElementById('root')!).render(
  <StrictMode>
    <WasmComponent />
  </StrictMode>,
)



