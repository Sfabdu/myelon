// myelon.tj — Официальный мост подключения к базе данных Supabase (2026)

// 1. НАСТРОЙКА КЛЮЧЕЙ (Вставь свои данные из заметок телефона внутрь кавычек)
const SUPABASE_URL = "https://pflswesjvkvprfreiyzs.supabase.co";
const SUPABASE_ANON_KEY = "sb_publishable_2pF3IxIXA7Ckp_HWGFbGsg_KoyCvW8JК";

// Функция для безопасных запросов к серверу в Сингапуре
async function supabaseRequest(endpoint, options = {}) {
    const url = ${SUPABASE_URL}/rest/v1/${endpoint};
    const headers = {
        "apikey": SUPABASE_ANON_KEY,
        "Authorization": Bearer ${SUPABASE_ANON_KEY},
        "Content-Type": "application/json",
        "Prefer": "return=representation"
    };

    try {
        const response = await fetch(url, { ...options, headers });
        if (!response.ok) throw new Error(Ошибка сервера: ${response.statusText});
        return await response.json();
    } catch (error) {
        console.error("Критический сбой моста Supabase:", error);
        return null;
    }
}

// 2. БЕСПЛАТНАЯ АВТОРИЗАЦИЯ (Тестовый безопасный режим без СМС)
async function authenticateUser(phoneNumber) {
    console.log(Запрос на вход для номера: ${phoneNumber});
    
    // Проверяем, существует ли уже такой пользователь в базе данных
    const existingUser = await supabaseRequest(users?phone=eq.${encodeURIComponent(phoneNumber)});
    
    if (existingUser && existingUser.length > 0) {
        console.log("Пользователь найден. Вход выполнен успешно!");
        localStorage.setItem("myelon_user", JSON.stringify(existingUser[0]));
        return existingUser[0];
    } else {
        console.log("Новый пользователь! Создаем чистый профиль в Supabase...");
        const newUser = {
            phone: phoneNumber,
            role: "user", // Обычный C2C профиль (как Авито)
            created_at: new Date().toISOString()
        };
        const result = await supabaseRequest("users", {
            method: "POST",
            body: JSON.stringify(newUser)
        });
        if (result && result.length > 0) {
            localStorage.setItem("myelon_user", JSON.stringify(result[0]));
            return result[0];
        }
    }
    return null;
}

// 3. ЖИВАЯ СВЯЗКА ДЛЯ КНОПКИ-ПЕРЕКЛЮЧАТЕЛЯ (Магазины vs Б_У)
async function loadLiveFeed(mode) {
    console.log(ИИ-Скрипт запрашивает из Сингапура товары режима: ${mode});
    
    // Делаем реальный запрос к таблице товаров с фильтром по типу объявления
    const items = await supabaseRequest(items?type=eq.${mode}&select=*);
    
    const grid = document.getElementById("feed-grid");
    if (!grid) return;

    if (!items || items.length === 0) {
        grid.innerHTML = <div style="grid-column: span 2; text-align: center; color: #9CA3AF; padding: 40px 0; font-size: 14px;">
            В этой категории пока нет активных объявлений. Будь первым, выложи свой товар!
        </div>;
        return;
    }

    // Очищаем ленту и заполняем её реальными данными из базы данных
    grid.innerHTML = "";
    items.forEach(item => {
        const badgeClass = item.type === 'shop' ? 'badge-shop' : 'badge-bu';
        const badgeText = item.type === 'shop' ? 'Магазин' : 'Б/У';
        
        grid.innerHTML += 
            <div class="card">
                <img class="card-img" src="${item.image_url || 'https://picsum.photos'}" alt="${item.title}">
                <div class="card-badge ${badgeClass}">${badgeText}</div>
                <div class="card-info">
                    <div class="card-price">${Number(item.price).toLocaleString()}<span>TJS</span></div>
                    <div class="card-title">${item.title}</div>
                    <div class="card-location">${item.location}</div>
                </div>
            </div>
        ;
    });
}