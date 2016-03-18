#include "scene.h"

/*

    удаление линий
        идти по массиву и сравнивать указатели с itemtAt
        потом удалить  и из массива и со сцены    // ЧТО ?


    ПРИ ПЕРЕКЛЮЧЕНИИ РЕЖИМОВ ОБНУЛЯТЬ ISPOINTSELECTED

*/

scena::scena()
{
    isPointSelected = NULL;
    cursor_chose = no_target;
}

scena::scena(QWidget *parent)
{
    isPointSelected = NULL;
      cursor_chose = no_target;//cursor_chose = add_point;
}

void scena::plusLine(point* from, point* to)
{

    int _from = get_num(from);
    int _to = get_num(to);
    matrix[_from][_to] = n(points[_from]->scenePos(), points[_to]->scenePos());
    matrix[_to][_from] = matrix[_from][_to];
    QPen pen;
    pen.setWidth(4);
    pen.setColor(Qt::gray);
    QLineF line(from->scenePos(),
                to->scenePos());
    line_item* o = new line_item(from, to, line,pen, QString::number(matrix[_from][_to]));
    QObject::connect(o, SIGNAL(_val(double,point*&,point*)), this, SLOT(set_matrix(double,point*&,point*&)));
    this->addItem(o);
    o->set_text();
    lines.push_back(o);

}

double scena::n(QPointF a, QPointF b)
{
    double x1 = a.x() , x2 = b.x();
    double y1 = a.y() , y2 = b.y();

    return sqrt( pow(x2-x1,2) + pow(y2-y1,2) );
}

void scena::addPoints(QPointF position)
{
    QTransform trans;
    point* tmp = dynamic_cast<point*>(itemAt(position, trans));

    if(tmp == NULL){
        point* pnt = new point(position);
        pnt->setZValue(1);
        addItem(pnt);
        points.push_back(pnt);
        QObject::connect(pnt, SIGNAL(point_is_move(point*, QPointF)), this, SLOT(point_move(point*,QPointF)));
        QObject::connect(pnt, SIGNAL(point_is_pressed(point*)), this, SLOT(point_pressed(point*)));
        QObject::connect(pnt, SIGNAL(point_is_unpressed(point*)), this, SLOT(point_unpressed(point*)));
    }
    for(int i = 0; i < matrix.size(); i++)
    {
        matrix[i].push_back(0);
    }

    matrix.push_back(QList< double >());

    for(int i = 0; i <matrix.size(); i++)
    {
        matrix[matrix.size() - 1].push_back(0);
    }

}

void scena::reDrawLines()
{
    return;
    for(int i = 0; i < lines.size(); i++)
    {
       // removeItem(lines[i]->my_text);
        removeItem(lines[i]);
         QObject::connect(lines[i], SIGNAL(_val(double)), this, SLOT(set_matrix(double,point*&,point*&)));
    }
    lines.clear();

    QPen pen;
    pen.setWidth(4);
    pen.setColor(Qt::gray);

    for(int i = 0; i < matrix.size(); i++)
    {
        for(int j = i; j < matrix.size(); j++)
        {
            if(matrix[i][j] > 0){
                QLineF line(points[i]->scenePos(),
                            points[j]->scenePos());
                line_item* o = new line_item(points[i], points[j], line,pen, QString::number(matrix[i][j]));
                QObject::connect(o, SIGNAL(_val(double,point*&,point*)), this, SLOT(set_matrix(double,point*&,point*&)));
                this->addItem(o);
                o->set_text();
                lines.push_back(o);
            }
        }
    }

}

void scena::set_matrix(double value, point *&a, point *&b)
{
    matrix[get_num(a)][get_num(b)] = value;
    matrix[get_num(b)][get_num(a)] = value;
    for(int i = 0; i < lines.size(); i++)
    {
        if( (lines[i]->p_1 == a) || ( lines[i]->p_2 == a) ){
            lines[i]->my_text->setPlainText(QString::number(value));
        }
    }
}

int scena::get_num(point *p)
{
    for(int i = 0; i < points.size(); i++)
    {
        if(points[i] == p)
            return i;
    }
    return -1;
}

void scena::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QTransform trans;
    point* tmp = dynamic_cast<point*>(itemAt(event->scenePos(), trans));

    qDebug()<<"pressed "<<itemAt(event->scenePos(), trans);

   // qDebug() << "Grabber is"<<mouseGrabberItem();
    switch(cursor_chose)
    {
    case add_point:

        addPoints(event->scenePos());
        break;

    case no_target:

            //here show info about point
         QGraphicsScene::mousePressEvent(event);
         return;
        break;

    case add_lines:

        if(tmp == NULL){
            isPointSelected = NULL;
        }
        break;

    case dijksta:

        if(tmp == NULL){
            isPointSelected = NULL;
        }
        break;

    case astar:

        if(tmp == NULL){
            isPointSelected = NULL;
        }
        break;
    case floyd:

        if(tmp == NULL){
            isPointSelected = NULL;
        }
        break;
    case remove_lines:
    {
        QGraphicsItem* new_tmp = itemAt(event->scenePos(), trans);
        if(new_tmp != NULL){
            for(int i = 0; i < lines.size() ; i++)
            {
                if(new_tmp == lines[i]){
                    removeItem(dynamic_cast<line_item*>(new_tmp)->my_text);
                    removeItem(new_tmp);
                    minusLine(get_num(dynamic_cast<point*>(itemAt(lines[i]->line().p1(),trans))),
                              get_num(dynamic_cast<point*>(itemAt(lines[i]->line().p2(),trans))));
                    //reDrawLines();
                    lines.removeAt(i);
                    break;
                }
            }
        }
        break;
    }
    case to_skip:

        cursor_chose = no_target;
        for(int i = 0; i < dijkstra_lines.size() ;i++)
            removeItem(dijkstra_lines[i]);
        dijkstra_lines.clear();
        QString nolik = " ";
        emit send_to_timeout_text(nolik, 10);
        break;

    }

 QGraphicsScene::mousePressEvent(event);
}

void scena::allRemove()
{
    for(int i = 0; i < dijkstra_lines.size() ;i++)
    {
        removeItem(dijkstra_lines[i]);
    }
    dijkstra_lines.clear();
    if(isPointSelected != NULL){
        isPointSelected->set_choosen(false);
        isPointSelected = NULL;
    }
}

void scena::dia()
{
    QVector<int> r = _d.dmtr(points, matrix);
    drawWay(r[0],r[1], alh.A_star(r[0],r[1],points,matrix));
    QString mfk = "Diametr = " + QString::number(r[2]);
    emit send_to_timeout_text(mfk, 5000);
}

void scena::drawLoops()
{
    QVector<int> minelay = alh.DFS(points,matrix);    // prost)

    for(int i = 0; i < minelay.size() - 1; i++)
    {
        if(minelay[i] != -1 && minelay[i+1] != -1){
            QLineF line(points[minelay[i]]->scenePos(), points[minelay[i+1]]->scenePos());
            QPen pen;
            pen.setWidth(6);
            pen.setColor(Qt::blue);
            dijkstra_lines.push_back(addLine(line,pen));
        }
    }
}

void scena::drawWay(int start, int end, QVector<int> way)
{
    while(end != start){
        QLineF line(points[end]->scenePos(), points[way[end]]->scenePos());
        QPen pen;
        pen.setWidth(8);
        pen.setColor(Qt::green);
        dijkstra_lines.push_back(addLine(line,pen));
        end = way[end];
    }
}

void scena::minusLine(int a, int i)
{

        matrix[i][a] = 0;
        matrix[a][i] = 0;

}

void scena::minusLine(line_item *line)
{
    this->removeItem(line->my_text);
    this->removeItem(line);
    for(int i = 0; i < lines.size(); i++)
        if(lines[i] == line){
            lines.removeAt(i);
            return;
        }
}

void scena::removePoint(point* my_p)
{
    int n = get_num(my_p);

    vector<line_item*>tmp_arr;
    for(int i = 0; i < lines.size() ; i++)
    {
        if( (lines[i]->p_1 == my_p) || (lines[i]->p_2 == my_p))
            tmp_arr.push_back(lines[i]);
    }

    for(int i = 0; i < tmp_arr.size(); i++)
    {
        for(int j = 0; j < lines.size(); j++)
        {
            if(lines[j] == tmp_arr[i]){
                QTransform trans;
                removeItem(lines[j]->my_text);

                minusLine(get_num(dynamic_cast<point*>(itemAt(lines[j]->line().p1(),trans))),
                          get_num(dynamic_cast<point*>(itemAt(lines[j]->line().p2(),trans))));
                removeItem(lines[j]);
                lines.removeAt(j);
                break;
            }
        }
    }

    for(int i = 0; i < matrix.size() ; i++)
    {
        matrix[i].removeAt(n);
    }
    matrix.removeAt(n);
    points.removeAt(n);

}

void scena::setCursorState(int m)
{
  cursor_chose = static_cast<cursorState>(m);
}

void scena::point_move(point *this_point, QPointF position)
{

  /*  for(int i = 0 ;i < points.size(); i++)
    {
        int _t_m = get_num(this_point);
        if(matrix[i][_t_m] > 0){
            matrix[i][_t_m] = n(this_point->scenePos(), points[i]->scenePos());
            matrix[_t_m][i] = matrix[i][_t_m];
        }
    }*/
    if(cursor_chose == no_target){

        this_point->setPos(position);
        QString f = "Chosed " + QString::number(get_num(this_point)) +
                    " point , pos = x:" +
                    QString::number(this_point->scenePos().x()) + " y:" +
                    QString::number(this_point->scenePos().y());

        emit send_to_permament_status(f);
        do_it(this_point);
        //reDrawLines();
    }
    if(cursor_chose == add_lines){
        this_point->setSelected(true);
        isPointSelected = this_point;           // костыль ?
       //  reDrawLines();
    }

}

void scena::do_it(point* a)
{
    for(int i = 0; i < lines.size(); i++)
    {
        if( lines[i]->p_1 == a ){
            QLineF line(a->scenePos(), lines[i]->p_2->scenePos());
            lines[i]->setLine(line);
            lines[i]->show();
        }
        if( lines[i]->p_2 == a ){
            QLineF line(lines[i]->p_1->scenePos() , a->scenePos());
            lines[i]->setLine(line);
            lines[i]->show();
        }
    }
    this->update();
}

void scena::point_pressed(point *this_point)
{
    if(cursor_chose == add_lines){
        if(isPointSelected != NULL){
            plusLine(this_point, dynamic_cast<point*>(isPointSelected));
            isPointSelected->setSelected(false);
            isPointSelected = this_point;
        }
        else{
            isPointSelected = this_point;
        }
    }

    if(cursor_chose == dijksta || cursor_chose == astar || cursor_chose == floyd){
        if(isPointSelected != NULL){
            int start = get_num(isPointSelected);
            int end = get_num(this_point);
            if(cursor_chose == dijksta)
                drawWay(start, end,
                        alh.Dijkstra(start, end, points, matrix));
            else if(cursor_chose == astar){
                drawWay(start, end,
                        alh.A_star(start,end,points,matrix));
            }
            else{
                drawWay(end, start,
                        f_w.floyd_warshall(start,end,points,matrix));
            }
            isPointSelected = NULL;
            cursor_chose = to_skip;
        }
        else{
            isPointSelected = this_point;
        }
        return;
    }

    if(cursor_chose == remove_points){
        QObject::disconnect(this_point, SIGNAL(point_is_move(point*)), this, SLOT(point_move(point*)));
        QObject::disconnect(this_point, SIGNAL(point_is_pressed(point*)), this, SLOT(point_pressed(point*)));
        QObject::disconnect(this_point, SIGNAL(point_is_unpressed(point*)), this, SLOT(point_unpressed(point*)));
        removeItem(dynamic_cast<QGraphicsItem*>(this_point));
        removePoint(this_point);
        points.removeAt(get_num(this_point));
      //  reDrawLines();
    }
    if(cursor_chose == no_target){
        QString f = "Chosed " + QString::number(get_num(this_point)) +
                " point , pos = x:" +
                QString::number(this_point->scenePos().x()) + " y:" +
                QString::number(this_point->scenePos().y());
        emit send_to_permament_status(f);
    }
}

void scena::point_unpressed(point *this_point)
{
    QString h = " ";
    emit send_to_permament_status(h);
}

void scena::skip()
{
    isPointSelected = NULL;
    foreach(auto point, this->points)
    {
        point->setSelected(false);
    }
}
