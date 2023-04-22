#ifndef CANVAS_H__

#define CANVAS_H__

#include <limits>

#include "Ray.h"
#include "Point.h"
#include "Matrix.h"
#include "utilities.h"
 

#include <optional>
/**

    @class   Canvas
    @brief   базовый класс холста
    @details ~ в этом класе находится \a Ray<Dot> points_to_draw_ и проходит обработка MAX_VIRTUAL_ и MIN_VIRTUAL_

**/
class Canvas
{
private:

	Point MAX_VIRTUAL_;			//!<   MAX_VIRTUAL_  точка созданная из максимальных координат переданных в холст

	Point MIN_VIRTUAL_;			//!<   MAX_VIRTUAL_  точка созданная из минимальных координат переданных в холст

	Ray<Dot> points_to_draw_;	//!< points_to_draw_  массив вида Ray<Dot>, содержит в себе все точки что должны будут быть нарисованы на холсте
 
	static const size_t NOT_POSITION = std::numeric_limits<size_t>::max(); //!<   NOT_POSITION значение флаг для возврата ошибки/не выполнено из функций 

	bool is_last_change_update_points_;		//!<   is_last_change_update_points_  Обновила ли массив точек points_to_draw_ последняя попытка добавления или удаления?

	bool is_last_change_update_min_;		//!<   is_last_change_update_min_ Обновила ли минимум MIN_VIRTUAL_ последняя попытка добавления или удаления?

	bool is_last_change_update_max_;		//!<  is_last_change_update_max_ Обновила ли максимум MAX_VIRTUAL_ последняя попытка добавления или удаления?

	//int coefficient_;
	//std::optional<size_t> search_point(const Dot& pt) const;

	void max_min_init_();
	void update_min_max_by(const Dot& pt);

 /**
     @fn     search_point
     @brief  функция ищет Dot в  \a Ray<Dot> points_to_draw_
     @param[in]  pt - точка Dot для поиска
     @retval    -  индекс найденной точки или size_t NOT_POSITION если точка не была найдена
 **/
	size_t search_point(const Dot& pt) const;

protected:
 /**
     @fn     MAX_VIRTUAL
     @brief  возвращает const MAX_VIRTUAL() const для использования в наследниках
     @retval  - MAX_VIRTUAL() const;
 **/
	const Point& MAX_VIRTUAL() const;

 /**
     @fn     MIN_VIRTUAL
     @brief  возвращает const MIN_VIRTUAL() const для использования в наследниках
     @retval  - MIN_VIRTUAL() const;
 **/
	const Point& MIN_VIRTUAL() const;

 /**
     @fn     points_to_draw
     @brief  возвращает const points_to_draw const для использования в наследниках
     @retval  - points_to_draw() const;
 **/
	const Ray<Dot>& points_to_draw() const;

 /**
     @fn     is_last_change_update_points
     @brief  дает возможность проверить были ли изменения в \a Ray<Dot> points_to_draw_ после последний попытки внести изменения
     @retval  - bool флаг, true если изменения были, false если не было
 **/
	bool is_last_change_update_points() const;

 /**
     @fn     is_last_change_update_max
     @brief  дает возможность проверить были ли изменения MAX_VIRTUAL
     @retval  - bool флаг, true если изменения были, false если не было
 **/
	bool is_last_change_update_max() const;

 /**
     @fn     is_last_change_update_min
     @brief  дает возможность проверить были ли изменения MIN_VIRTUAL
     @retval  - bool флаг, true если изменения были, false если не было
 **/
	bool is_last_change_update_min() const;


public:
 /**
     @fn    Canvas
     @brief Canvas object constructor
 **/
	Canvas();
 
	Canvas& operator+=(const Canvas& other);
 
 /**
     @fn    insert
     @brief функция добавления точки c символом в массив для отрисовки
     @param[in] pt - Dot& pt, координаты точки с символом для отрисовки
 **/
	void insert(const Dot& pt);

 /**
     @fn    insert
     @brief функция добавления точки в массив для отрисовки, символ по умолчанию '.'
     @param pt[in] - Point& pt, координаты точки с символом для отрисовки
     @param symbol - по умолчанию char symbol = '.'
 **/
	void insert(const Point& pt, char symbol = '.');

 /**
     @fn    insert
     @brief  функция добавления массива точек в массив для отрисовки, символ по умолчанию '.'
     @param points - Ray<Point>& points, динамический массив дочек
     @param symbol - по умолчанию char symbol = '.'
 **/
	void insert(const Ray<Point>& points, char symbol = '.');

 /**
     @fn    insert
     @brief  функция добавления массива точек в массив для отрисовки
     @param points - Ray<Dot>& points, динамический массив Dot
 **/
	void insert(const Ray<Dot>& points);

 /**
     @fn    remove
     @brief функция удаления точек из массива точек для отрисовки
     @param[in] dl                  - точка для удаления
     @param[in] isUpdateCanvasSizes - флаг для перерасчета MAX_VIRTUAL() и MIN_VIRTUAL() при изменении крайних точек в массиве
 **/
	void remove(const Point& dl, bool isUpdateCanvasSizes = false);

 /**
     @fn    insert_line
     @brief функция для расчета точек линии и добавление их в массив в массив дял рисования
     @param[in] A      - точка начала линии
     @param[in] B      - точка конца линии 
     @param[in] symbol - сивол которым будет нарисована линия 
 **/
	void insert_line(const Dot& A, const Dot& B, char symbol);

 /**
     @fn    remove_line
     @brief функция удаления линии с массива для рисования
     @param[in] A -  точка начала удаления линии
     @param[in] B -  точка конца удаления линии 
 **/
	void remove_line(const Dot& A, const Dot& B);

 /**
     @fn    remove
     @brief функция для удаления массива Point с массива для рисования
     @param[in] points -  Ray<Point>& points массив значения из которого будут найдены и удалены
 **/
	void remove(const Ray<Point>& points);

 /**
     @fn    remove
     @brief функция для удаления массива Dot с массива для рисования
     @param[in] points - Ray<Dot>& points массив значения из которого будут найдены и удалены
 **/
	void remove(const Ray<Dot>& points);

 /**
     @fn     is_point
     @brief  функция для поиска Dot& pt в массиве для рисования
     @param[in]  pt - точка которую будут искать в массиве для рисования
     @retval    - true если точка была найдена, false если нет
 **/
	bool is_point(const Dot& pt) const;

	~Canvas() = default;
};

#endif //!  CANVAS_H__