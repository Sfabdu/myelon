// Функция, которая сама создаст и вставит шторку Авито на экран
function injectFilterModal() {
    const modalHTML = 
    <div id="filter-modal" class="filter-backdrop">
        <div class="filter-sheet">
            <!-- Шапка шторки -->
            <div class="filter-header">
                <span class="close-filter-btn" onclick="closeFilterModal()">✕</span>
                <h3>Фильтры</h3>
                <span class="reset-filter-btn" onclick="alert('Сбросить все фильтры')">Сбросить</span>
            </div>

            <!-- Тело фильтров -->
            <div class="filter-body">
                <!-- Блок Город -->
                <div class="filter-group">
                    <label>Где искать</label>
                    <select id="filter-city">
                        <option value="all">Весь Таджикистан</option>
                        <option value="dushanbe">Душанбе</option>
                        <option value="khujand">Худжанд</option>
                        <option value="bokhtar">Бохтар</option>
                    </select>
                </div>

                <!-- Блок Цена -->
                <div class="filter-group">
                    <label>Цена, TJS</label>
                    <div class="price-input-row">
                        <input type="number" id="price-from" placeholder="от">
                        <input type="number" id="price-to" placeholder="до">
                    </div>
                </div>

                <!-- Блок Продавцы -->
                <div class="filter-group">
                    <label>Продавцы</label>
                    <div class="seller-toggle-row">
                        <button class="seller-type-btn active" onclick="setSellerType(this)">Все</button>
                        <button class="seller-type-btn" onclick="setSellerType(this)">Частные</button>
                        <button class="seller-type-btn" onclick="setSellerType(this)">Компании</button>
                    </div>
                </div>
            </div>

            <!-- Финальная кнопка в самом низу -->
            <div class="filter-footer-btn-box">
                <button class="btn-apply-filters" onclick="closeFilterModal()">Показать объявления</button>
            </div>
        </div>
    </div>
    ;

    // Вставляем этот код в самый конец страницы перед закрытием body
    document.body.insertAdjacentHTML('beforeend', modalHTML);
}

// Функции управления шторкой
function openFilterModal() {
    document.getElementById('filter-modal').classList.add('open');
}
function closeFilterModal() {
    document.getElementById('filter-modal').classList.remove('open');
}
function setSellerType(btn) {
    document.querySelectorAll('.seller-type-btn').forEach(b => b.classList.remove('active'));
    btn.classList.add('active');
}

// Запускаем автоматическую сборку шторки при загрузке страницы
document.addEventListener("DOMContentLoaded", injectFilterModal);
