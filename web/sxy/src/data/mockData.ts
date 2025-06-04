// 定义基础类型
interface BaseProduct {
  id: number;
  name: string;
  price: number;
  image: string;
  category: string;
  discount?: number;
  featured?: boolean;
}

// 商品详情接口
interface ProductDetail extends BaseProduct {
  images: string[];
  description: string;
  sizes: string[];
  colors: string[];
  stock: number;
  sku: string;
  reviews: Review[];
}

// 评论接口
interface Review {
  id: number;
  user: string;
  rating: number;
  comment: string;
  date: string;
}

// 地址接口
interface Address {
  id: number;
  name: string;
  phone: string;
  province: string;
  city: string;
  district: string;
  detail: string;
  isDefault: boolean;
}

// 订单项接口
interface OrderItem {
  id: number;
  name: string;
  price: number;
  image: string;
  quantity: number;
  discount?: number;
}

// 订单接口
interface Order {
  id: string;
  date: string;
  status: 'pending' | 'processing' | 'shipped' | 'delivered' | 'cancelled';
  total: number;
  items: OrderItem[];
}

// 用户接口
interface User {
  id: number;
  name: string;
  email: string;
  phone: string;
  avatar: string;
  address: Address[];
}

// 首页轮播图数据
export const carouselItems = [
  {
    id: 1,
    image: '/img/carouse/1.avif',
    title: '2025 春季新品',
    description: '探索我们最新的春季系列，展现自信与风格',
    buttonText: '立即购买',
    buttonLink: '#',
  },
  {
    id: 2,
    image: '/img/carouse/2.avif',
    title: '限时折扣',
    description: '精选商品低至5折，限时特惠',
    buttonText: '查看详情',
    buttonLink: '#',
  },
  {
    id: 3,
    image: '/img/carouse/3.avif',
    title: '独家系列',
    description: '发现我们的设计师合作系列，独特而时尚',
    buttonText: '探索系列',
    buttonLink: '#',
  },
];

// 分类数据
export const categories = [
  { id: 1, name: '女装', image: '/img/categories/1.avif' },
  { id: 2, name: '男装', image: '/img/categories/2.avif' },
  { id: 3, name: '配饰', image: '/img/categories/3.avif' },
  { id: 4, name: '鞋履', image: '/img/categories/4.avif' },
  { id: 5, name: '包袋', image: '/img/categories/5.avif' },
];

// 商品基础数据
const baseProducts: BaseProduct[] = [
  { id: 1, name: '时尚连衣裙', price: 299, image: '/img/baseProducts/1.avif', discount: 0.8, category: 'women', featured: true },
  { id: 2, name: '休闲西装', price: 599, image: '/img/baseProducts/2.avif', category: 'men' },
  { id: 3, name: '复古太阳镜', price: 129, image: '/img/baseProducts/3.avif', category: 'accessories' },
  { id: 4, name: '真皮手提包', price: 499, image: '/img/baseProducts/4.avif', discount: 0.7, category: 'accessories', featured: true },
  { id: 5, name: '运动鞋', price: 399, image: '/img/baseProducts/5.avif', category: 'men' },
  { id: 6, name: '牛仔夹克', price: 459, image: '/img/baseProducts/6.avif', category: 'men' },
  { id: 7, name: '丝巾', price: 99, image: '/img/baseProducts/7.avif', discount: 0.5, category: 'accessories', featured: true },
  { id: 8, name: '皮带', price: 159, image: '/img/baseProducts/8.avif', category: 'accessories' },
  { id: 9, name: '针织毛衣', price: 329, image: '/img/baseProducts/9.avif', category: 'women' },
  { id: 10, name: '休闲裤', price: 259, image: '/img/baseProducts/10.avif', category: 'men' },
  { id: 11, name: '女士衬衫', price: 229, image: '/img/baseProducts/11.avif', category: 'women' },
  { id: 12, name: '高跟鞋', price: 349, image: '/img/baseProducts/12.avif', discount: 0.8, category: 'women', featured: true },
];

// 导出所有商品
export const allProducts = baseProducts;

// 商品详情数据
export const productDetails: ProductDetail[] = baseProducts.map(product => {
  // 为每个商品设置对应的图片集合
  let productImages: string[] = [product.image];
  
  // 根据商品ID或类别添加对应的图片
  switch (product.id) {
    case 1: // 时尚连衣裙
      productImages.push(
        '/img/productDetails/a2.avif',
      );
      break;
    case 2: // 休闲西装
      productImages.push(
        '/img/productDetails/b1.avif',
        '/img/productDetails/b2.avif',
      );
      break;
    case 3: // 复古太阳镜
      productImages.push(
        '/img/productDetails/c1.avif',
        '/img/productDetails/c2.avif',
      );
      break;
    case 4: // 真皮手提包
      productImages.push(
        '/img/productDetails/d1.avif',
        '/img/productDetails/d2.avif',
      );
      break;
    case 5: // 运动鞋
      productImages.push(
        '/img/productDetails/e1.avif',
        '/img/productDetails/e2.avif',
      );
      break;
    case 6: // 牛仔夹克
      productImages.push(
        '/img/productDetails/f1.avif',
        '/img/productDetails/f2.avif',
      );
      break;
    case 9: // 针织毛衣
      productImages.push(
        '/img/productDetails/g1.avif',
        '/img/productDetails/g2.avif',
      );
      break;
    case 10: // 休闲裤
      productImages.push(
        '/img/productDetails/j1.avif',
        '/img/productDetails/j2.avif',
      );
      break;
    case 11: // 女士衬衫
      productImages.push(
        '/img/productDetails/i1.avif',
        '/img/productDetails/i2.avif',
      );
      break;
    case 12: // 高跟鞋
      productImages.push(
        '/img/productDetails/k1.avif',
        '/img/productDetails/k2.avif',
      );
      break;
    default:
      // 如果没有特定的图片，使用通用图片
      productImages.push(
        '/img/productDetails/t.avif',
      );
  }
  
  // 为不同类别设置不同的尺码
  let sizes: string[];
  if (product.category === 'women' || product.category === 'men') {
    sizes = ['S', 'M', 'L', 'XL'];
  } else if (product.id === 5 || product.id === 12) { // 鞋子
    sizes = ['36', '37', '38', '39', '40', '41', '42'];
  } else {
    sizes = ['均码'];
  }

  // 根据商品类型设置合适的颜色选项
  let colors: string[];
  switch (product.id) {
    case 1: // 连衣裙
      colors = ['黑色', '白色', '蓝色'];
      break;
    case 2: // 西装
      colors = ['黑色', '灰色', '藏青色'];
      break;
    case 3: // 太阳镜
      colors = ['黑色', '棕色', '金色'];
      break;
    case 4: // 手提包
      colors = ['黑色', '棕色', '红色'];
      break;
    case 5: // 运动鞋
      colors = ['白色', '黑色', '红色'];
      break;
    case 6: // 牛仔夹克
      colors = ['蓝色', '黑色', '灰色'];
      break;
    case 7: // 丝巾
      colors = ['红色', '蓝色', '紫色'];
      break;
    case 8: // 皮带
      colors = ['黑色', '棕色'];
      break;
    case 9: // 针织毛衣
      colors = ['米色', '灰色', '蓝色'];
      break;
    case 10: // 休闲裤
      colors = ['黑色', '卡其色', '灰色'];
      break;
    case 11: // 女士衬衫
      colors = ['白色', '蓝色', '粉色'];
      break;
    case 12: // 高跟鞋
      colors = ['黑色', '红色', '银色'];
      break;
    default:
      colors = ['黑色', '白色', '蓝色'];
  }

  // 生成评论
  const reviewUsers = ['张小姐', '李女士', '王先生', '赵女士', '刘先生'];
  const reviewComments = [
    '质量很好，面料舒适，尺码也很合适，很满意的一次购物体验。',
    '款式很漂亮，就是快递有点慢。',
    '非常合身，质量也很好，值得购买。',
    '颜色和图片一致，很满意。',
    '性价比很高，推荐购买。'
  ];
  const reviewCount = Math.floor(Math.random() * 3) + 1; // 1-3条评论
  const reviews = Array.from({ length: reviewCount }, (_, i) => ({
    id: i + 1,
    user: reviewUsers[Math.floor(Math.random() * reviewUsers.length)],
    rating: Math.floor(Math.random() * 2) + 4, // 4-5星评价
    comment: reviewComments[Math.floor(Math.random() * reviewComments.length)],
    date: `2023-${String(Math.floor(Math.random() * 12) + 1).padStart(2, '0')}-${String(Math.floor(Math.random() * 28) + 1).padStart(2, '0')}`
  }));

  // 为每个商品设置更具体的描述
  let description: string;
  switch (product.id) {
    case 1:
      description = '这款连衣裙采用优质面料制作，手感柔软，穿着舒适。简约大方的设计风格，适合各种场合穿着。精致的剪裁勾勒出优美的身材曲线，是您日常和特殊场合的理想选择。';
      break;
    case 2:
      description = '这款休闲西装采用高品质混纺面料，穿着舒适透气。经典剪裁与现代设计相结合，适合商务会议或正式场合穿着。内衬采用优质里料，细节处理精致，彰显专业品质。';
      break;
    case 3:
      description = '这款复古太阳镜采用高品质材料制作，镜片具有UV400防护功能，有效阻挡有害紫外线。复古的设计风格与现代工艺相结合，提供舒适的佩戴体验和时尚的外观。';
      break;
    case 4:
      description = '这款真皮手提包选用优质头层牛皮制作，手感柔软，质感出众。精湛的工艺和细致的缝线彰显高级感，内部空间宽敞，设有多个功能隔层，满足您的日常收纳需求。';
      break;
    case 5:
      description = '这款运动鞋采用轻质材料和人体工学设计，提供卓越的舒适性和支撑性。鞋底具有出色的抓地力和缓震性能，适合日常运动和休闲穿着，时尚的外观设计使其成为百搭单品。';
      break;
    case 6:
      description = '这款牛仔夹克采用优质牛仔面料制作，经典的水洗工艺使其穿着舒适且富有质感。细节处理精致，版型修身不紧绷，是打造休闲时尚风格的必备单品。';
      break;
    case 7:
      description = '这款丝巾采用优质真丝材质，触感柔滑，色彩鲜艳持久。精美的印花设计展现艺术气息，多种系法满足不同场合需求，为您的穿搭增添亮点。';
      break;
    case 8:
      description = '这款皮带采用优质头层牛皮制作，坚固耐用且富有质感。精致的金属扣设计简约大方，适合商务或休闲场合使用，是男士穿搭的必备单品。';
      break;
    case 9:
      description = '这款针织毛衣采用优质混纺纱线编织而成，保暖舒适不刺肤。简约的设计风格使其易于搭配，宽松的版型穿着舒适，是秋冬季节的理想选择。';
      break;
    case 10:
      description = '这款休闲裤采用高品质混纺面料，穿着舒适透气且不易起皱。合身的剪裁提供良好的活动自由度，简约的设计风格使其成为百搭单品，适合各种场合穿着。';
      break;
    case 11:
      description = '这款女士衬衫采用优质棉质面料，手感柔软，穿着舒适透气。简约大方的设计风格，精致的剪裁展现女性优雅气质，适合职场或日常穿着，是打造多种风格的基础单品。';
      break;
    case 12:
      description = '这款高跟鞋采用优质材料制作，鞋面设计简约优雅，鞋跟高度适中，穿着舒适稳定。内里填充柔软，长时间穿着也不会感到不适，是正式场合和日常穿搭的理想选择。';
      break;
    default:
      description = `这款${product.name}采用优质材料制作，品质卓越，设计时尚。精湛的工艺和细节处理，让您在各种场合都能展现自信风采。`;
  }

  return {
    ...product,
    images: productImages,
    description,
    sizes,
    colors,
    stock: Math.floor(Math.random() * 20) + 5, // 5-24件库存
    sku: `${product.category.substring(0, 1).toUpperCase()}${product.id}-${Math.floor(1000 + Math.random() * 9000)}`,
    reviews
  };
});

// 相关商品推荐 (使用ID引用基础商品)
export const relatedProducts = [9, 11, 12, 4].map(id => baseProducts.find(p => p.id === id)!);

// 推荐商品 (使用ID引用基础商品)
export const recommendedProducts = [5, 9, 12, 6].map(id => baseProducts.find(p => p.id === id)!);

// 筛选选项
export const filterOptions = {
  price: [
    { label: '全部价格', value: 'all' },
    { label: '¥0 - ¥199', value: '0-199' },
    { label: '¥200 - ¥399', value: '200-399' },
    { label: '¥400+', value: '400-9999' },
  ],
  sort: [
    { label: '推荐', value: 'recommended' },
    { label: '价格: 低到高', value: 'price-asc' },
    { label: '价格: 高到低', value: 'price-desc' },
    { label: '最新上架', value: 'newest' },
  ]
};

// 用户数据
export const userData: User = {
  id: 1,
  name: '张三',
  email: 'zhangsan@example.com',
  phone: '13800138000',
  avatar: '/img/u.avif',
  address: [
    {
      id: 1,
      name: '张三',
      phone: '13800138000',
      province: '北京市',
      city: '北京市',
      district: '朝阳区',
      detail: '建国路88号',
      isDefault: true,
    },
    {
      id: 2,
      name: '张三',
      phone: '13900139000',
      province: '上海市',
      city: '上海市',
      district: '浦东新区',
      detail: '陆家嘴金融中心',
      isDefault: false,
    },
  ],
};

// 订单数据
export const orderData: Order[] = [
  {
    id: 'ORD-2023-1001',
    date: '2023-05-15',
    status: 'delivered',
    total: 598,
    items: [
      { id: 1, name: '时尚连衣裙', price: 299, image: baseProducts[0].image, quantity: 1 },
      { id: 2, name: '休闲西装', price: 599, image: baseProducts[1].image, quantity: 1, discount: 0.5 },
    ],
  },
  {
    id: 'ORD-2023-0897',
    date: '2023-04-20',
    status: 'delivered',
    total: 349,
    items: [
      { id: 3, name: '高跟鞋', price: 349, image: baseProducts[11].image, quantity: 1 },
    ],
  },
  {
    id: 'ORD-2023-0756',
    date: '2023-03-10',
    status: 'delivered',
    total: 499,
    items: [
      { id: 4, name: '真皮手提包', price: 499, image: baseProducts[3].image, quantity: 1 },
    ],
  },
];

// 收藏数据 (使用ID引用基础商品)
export const favoriteData = [1, 3, 7, 12].map(id => baseProducts.find(p => p.id === id)!); 