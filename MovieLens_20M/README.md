# MovieLens_20M
Датасет: [MovieLens](https://www.kaggle.com/datasets/grouplens/movielens-20m-dataset)

Способы разбиения данных: Были рассмотрены Leave One Last Item, Leave One Last Basket/Session, User Spli

Использованные методы: Temporal Global, Temporal User, Random Split 

Оценка: Рассмотренные: RMSE, MSE, MAE Использованная оценка: RMSE

Алгоритмы: Collaborative Filtering на основе SVD, kNN, CoClustering; implicit-ALS; Гибридный подход:LightFM

Лучшим алгоритмом оказался CF-SVD, best RMSE: 0.7808 на стандартизованных данных

## Использованная информация (с коментариями):

Основная задача: https://www.kaggle.com/datasets/grouplens/movielens-20m-dataset

Список изученного: 
1. Цикл статей, item-based алгоритмы, user-based алгоритмы (collaboration filtering SVD, KNN)

https://medium.com/analytics-vidhya/the-world-of-recommender-systems-e4ea504341ac 

https://medium.com/analytics-vidhya/recommendation-system-using-collaborative-filtering-cc310e641fde

https://medium.com/@saketgarodia/metadata-based-recommender-systems-in-python-c6aae213b25c

2. Статья объясняющая как работает implicit-ALS CF + реализация
https://medium.com/radon-dev/als-implicit-collaborative-filtering-5ed653ba39fe 

3. http://www.machinelearning.ru/wiki/images/archive/9/95/20210411002205%21Voron-ML-CF.pdf  

4.  Оригинальная статья по коллаборативной фильтрации Implicit 
Collaborative Filtering for Implicit Feedbzck Datasets 
http://yifanhu.net/PUB/cf.pdf 

5.  Статья по проблемам рекомендательных систем (2021) 
https://habr.com/ru/company/prequel/blog/567648/

6. Сравнение implicit-ALS и множества других алгоритмов, крутая визуализация 
http://www.benfrederickson.com/matrix-factorization/

7. Простая реализация implicit-mf 
https://github.com/MrChrisJohnson/implicit-mf/blob/master/mf.py

8. (2018)Статья от ЛАНИТ "Анатомия рекомендательных систем" есть описание способов стандартизации данных + обснование реком https://habr.com/ru/company/lanit/blog/420499/

9. (2018)Статья от ЛАНИТ "Анатомия рекомендательных систем" есть оценка качества системы (Полезная статья, буду использовать оценки качества из статьи + есть информация о гибридных решениях, то что понадобится во второй части задачи)

10. Цикл статей за 2012 год про рекомендательные системы

*   https://habr.com/ru/company/surfingbird/blog/139022/
Постановка задачи
*   https://habr.com/ru/company/surfingbird/blog/139518/
Отличие user-based и item-based рекомендательных систем
*   https://habr.com/ru/company/surfingbird/blog/139863/
SVD, часть I
*   https://habr.com/ru/company/surfingbird/blog/140555/ 
SVD и базовые предикторы
*   https://habr.com/ru/company/surfingbird/blog/143455/ 
оверфиттинг и регуляризация
*   https://habr.com/ru/company/surfingbird/blog/150207/
теорема Байеса и наивный байесовский классификатор

11. ООооочень простая статья, чтобы разобраться что такое рекомендательные системы и какие подходы есть + картинки с англ надписями, чтобы въехать в терминологию 
https://habr.com/ru/company/piter/blog/350346/ 

12. Рекомендации с обоснованием, возможно найдётся сравнение метрик
https://habr.com/ru/post/550558/ 

13. https://realpython.com/build-recommendation-engine-collaborative-filtering/#using-python-to-build-recommenders

14. https://arxiv.org/pdf/2007.13237.pdf  Статья о том как дробить данные для рекомендательных систем

15. Kim Falk "Practical Recommender Systems" крутая книга по рекоммендательным системам
