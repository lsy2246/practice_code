import { HashRouter as Router, Routes, Route } from 'react-router-dom';
import Layout from './components/layout/Layout';
import Home from './pages/Home';
import ProductList from './pages/ProductList';
import Products from './pages/Products';
import ProductDetail from './pages/ProductDetail';
import Cart from './pages/Cart';
import UserProfile from './pages/UserProfile';
import SearchResults from './pages/SearchResults';
import NotFound from './pages/NotFound';
import { CartProvider } from './contexts/CartContext';
import { FavoriteProvider } from './contexts/FavoriteContext';

function App() {
  return (
    <Router>
      <CartProvider>
        <FavoriteProvider>
          <Routes>
            <Route path="/" element={<Layout />}>
              <Route index element={<Home />} />
              <Route path="products" element={<Products />} />
              <Route path="category/:category" element={<ProductList />} />
              <Route path="products/:id" element={<ProductDetail />} />
              <Route path="cart" element={<Cart />} />
              <Route path="profile" element={<UserProfile />} />
              <Route path="search" element={<SearchResults />} />
              <Route path="*" element={<NotFound />} />
            </Route>
          </Routes>
        </FavoriteProvider>
      </CartProvider>
    </Router>
  );
}

export default App;
