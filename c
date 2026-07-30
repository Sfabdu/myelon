<!DOCTYPE html>
<html lang="ru">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Дашборд продавца — myelon.tj</title>
    <link rel="stylesheet" href="assets/styles.css" />
    <script src="assets/app.js" defer></script>
    <style>
      .stats-chart { display: flex; align-items: flex-end; gap: 6px; height: 140px; margin-top: 8px; }
      .chart-bar { flex: 1; background: linear-gradient(180deg, var(--orange) 0%, #ff8b3d 100%); border-radius: 6px 6px 0 0; position: relative; min-height: 2px; transition: height 0.3s ease; }
      .chart-bar .bar-value { position: absolute; top: -18px; left: 50%; transform: translateX(-50%); font-size: 10px; font-weight: 600; color: #0f172a; white-space: nowrap; }
      .chart-bar .bar-label { position: absolute; bottom: -16px; left: 50%; transform: translateX(-50%); font-size: 9px; color: #94a3b8; white-space: nowrap; }
      .chart-axis { display: flex; justify-content: space-between; margin-top: 16px; color: #94a3b8; font-size: 10px; }
      .sales-table { display: grid; gap: 8px; margin-top: 12px; }
      .sales-row { display: grid; grid-template-columns: 1fr 1fr 1fr; padding: 10px 0; border-bottom: 1px solid #f1f5f9; font-size: 13px; }
      .sales-row:last-child { border-bottom: none; }
      .sales-row .row-label { color: #64748b; }
      .sales-row .row-value { text-align: right; font-weight: 600; color: #0f172a; }
      .sales-row .row-change { text-align: center; font-size: 11px; }
      .change-positive { color: #10b981; }
      .change-negative { color: #ef4444; }
      .stats-grid { display: grid; grid-template-columns: repeat(3, 1fr); gap: 12px; margin-bottom: 16px; }
      .stat-card { background: #f8f9fa; border: 1px solid #e2e8f0; border-radius: 12px; padding: 12px; text-align: center; }
      .stat-card .stat-value { font-size: 18px; font-weight: 700; color: #0f172a; }
      .stat-card .stat-label { font-size: 10px; color: #94a3b8; margin-top: 4px; }
      .chart-container { background: #fff; border: 1px solid #e2e8f0; border-radius: 16px; padding: 16px; margin-top: 12px; }
      .chart-title { font-size: 13px; font-weight: 600; color: #64748b; margin-bottom: 8px; }
      .chart-legend { display: flex; gap: 16px; margin-top: 8px; font-size: 11px; color: #94a3b8; }
      .legend-item { display: flex; align-items: center; gap: 6px; }
      .legend-dot { width: 8px; height: 8px; border-radius: 50%; background: var(--orange); }
    </style>
  </head>
  <body>
    <div class="page-shell">
      <header class="topbar">
        <button class="back-button" onclick="history.back()" title="Назад">←</button>
        <a class="brand" href="index.html">
          <span class="brand-mark">E</span>
          <span class="brand-text">
            <strong>myelon.tj</strong>
            <small data-i18n="brandSmall">Маркетплейс</small>
          </span>
        </a>
        <div class="top-actions">
          <button class="lang-switch" id="langToggle" type="button" data-i18n="langToggle">Тоҷикӣ</button>
          <nav class="top-nav">
            <a href="index.html" data-i18n="navMarketplace">Маркет</a>
            <a href="profile.html" data-i18n="navProfile">Профиль</a>
            <a href="seller.html" class="active" data-i18n="navSeller">Продавец</a>
            <a href="login.html" data-i18n="navLogin">Вход</a>
          </nav>
        </div>
      </header>

      <main class="dashboard-grid seller-grid">
        <section class="panel hero-panel">
          <div class="section-heading">
            <h2 data-i18n="sellerWorkspace">Рабочее пространство бизнеса</h2>
            <a href="#" data-i18n="sellerInsights">Живые аналитики</a>
          </div>
          <div class="kpi-row">
            <div class="kpi-card">
              <small data-i18n="sellerRevenue">Ежедневный доход</small>
              <strong>4,820 TJS</strong>
            </div>
            <div class="kpi-card">
              <small data-i18n="sellerOrders">Ожидающие заказы</small>
              <strong>21</strong>
            </div>
            <div class="kpi-card">
              <small data-i18n="sellerRepeat">Повторные покупатели</small>
              <strong>87%</strong>
            </div>
          </div>
          <div class="alert-box">
            <h3 data-i18n="sellerAlertTitle">Оповещение о вечернем сборе</h3>
            <p data-i18n="sellerAlertText">Курьер Elon должен забрать 8 премиальных посылок из вашего адреса в 19:30.</p>
          </div>
        </section>

        <!-- Statistics with charts -->
        <section class="panel">
          <div class="section-heading">
            <h2>Статистика продаж</h2>
            <a href="#" style="font-size: 12px; color: #64748b;">Сегодня • Неделя • Месяц</a>
          </div>
          <div class="stats-grid">
            <div class="stat-card">
              <div class="stat-value">12 450 TJS</div>
              <div class="stat-label">Сегодня</div>
            </div>
            <div class="stat-card">
              <div class="stat-value">87 200 TJS</div>
              <div class="stat-label">На этой неделе</div>
            </div>
            <div class="stat-card">
              <div class="stat-value">342 800 TJS</div>
              <div class="stat-label">В этом месяце</div>
            </div>
          </div>

          <div class="chart-container">
            <div class="chart-title">Ежедневные продажи (7 дней)</div>
            <div class="stats-chart" id="dailyChart">
              <div class="chart-bar" style="height: 60%;" data-value="8 200" data-label="Пн">
                <span class="bar-value">8.2к</span>
                <span class="bar-label">Пн</span>
              </div>
              <div class="chart-bar" style="height: 85%;" data-value="11 500" data-label="Вт">
                <span class="bar-value">11.5к</span>
                <span class="bar-label">Вт</span>
              </div>
              <div class="chart-bar" style="height: 45%;" data-value="6 100" data-label="Ср">
                <span class="bar-value">6.1к</span>
                <span class="bar-label">Ср</span>
              </div>
              <div class="chart-bar" style="height: 100%;" data-value="13 400" data-label="Чт">
                <span class="bar-value">13.4к</span>
                <span class="bar-label">Чт</span>
              </div>
              <div class="chart-bar" style="height: 75%;" data-value="10 100" data-label="Пт">
                <span class="bar-value">10.1к</span>
                <span class="bar-label">Пт</span>
              </div>
              <div class="chart-bar" style="height: 90%;" data-value="12 200" data-label="Сб">
                <span class="bar-value">12.2к</span>
                <span class="bar-label">Сб</span>
              </div>
              <div class="chart-bar" style="height: 55%;" data-value="7 500" data-label="Вс">
                <span class="bar-value">7.5к</span>
                <span class="bar-label">Вс</span>
              </div>
            </div>
            <div class="chart-legend">
              <div class="legend-item"><span class="legend-dot"></span> Выручка</div>
              <div class="legend-item"><span class="legend-dot" style="background: #cbd5e1;"></span> Цель: 15.0к</div>
            </div>
          </div>

          <div class="chart-container" style="margin-top: 16px;">
            <div class="chart-title">Анализ продаж по категориям</div>
            <div class="sales-table">
              <div class="sales-row">
                <span class="row-label">Электроника</span>
                <span class="row-value">124 500 TJS</span>
                <span class="row-change change-positive">+12% ↗</span>
              </div>
              <div class="sales-row">
                <span class="row-label">Одежда</span>
                <span class="row-value">68 200 TJS</span>
                <span class="row-change change-positive">+5% ↗</span>
              </div>
              <div class="sales-row">
                <span class="row-label">Дом и сад</span>
                <span class="row-value">42 100 TJS</span>
                <span class="row-change change-negative">-3% ↘</span>
              </div>
              <div class="sales-row">
                <span class="row-label">Транспорт</span>
                <span class="row-value">108 000 TJS</span>
                <span class="row-change change-positive">+18% ↗</span>
              </div>
              <div class="sales-row">
                <span class="row-label">Услуги</span>
                <span class="row-value">28 500 TJS</span>
                <span class="row-change change-negative">-7% ↘</span>
              </div>
            </div>
          </div>
        </section>

        <section class="panel">
          <div class="section-heading">
            <h2 data-i18n="sellerShipments">Ожидающие отправки</h2>
            <a href="#" data-i18n="sellerRoute">Маршрут</a>
          </div>
          <div class="table-card">
            <div class="table-row"><span>Заказ #1082</span><span data-i18n="sellerNorth">Северный Душанбе</span><span>18:20</span></div>
            <div class="table-row"><span>Заказ #1084</span><span data-i18n="sellerSouth">Южный Душанбе</span><span>19:00</span></div>
            <div class="table-row"><span>Заказ #1087</span><span data-i18n="sellerKhujand">Худжанд</span><span>22:10</span></div>
          </div>
        </section>

        <section class="panel review-panel">
          <div class="section-heading">
            <h2 data-i18n="sellerFeedback">Система отзывов</h2>
            <a href="#" data-i18n="sellerProof">Загрузить подтверждение</a>
          </div>
          <form class="review-form">
            <input type="text" data-i18n-placeholder="sellerName" placeholder="Ваше имя" />
            <textarea rows="4" data-i18n-placeholder="sellerReview" placeholder="Опишите ваш опыт с товаром"></textarea>
            <label class="upload-box">
              <input type="file" />
              <span data-i18n="sellerUpload">Загрузить фото подтверждения покупки</span>
            </label>
            <button class="primary-btn" type="button" data-i18n="sellerPublish">Опубликовать отзыв</button>
          </form>
          <div class="review-list">
            <article class="review-card">
              <strong>Фарида</strong>
              <p data-i18n="sellerReviewOne">«Доставка пришла точно в срок. Очень красивая упаковка.»</p>
              <span>★★★★★</span>
            </article>
            <article class="review-card">
              <strong>Рустам</strong>
              <p data-i18n="sellerReviewTwo">«Отличное качество товара и хорошая коммуникация.»</p>
              <span>★★★★★</span>
            </article>
          </div>
        </section>
      </main>
    </div>
  </body>
</html>
