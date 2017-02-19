#include "scene.h"

scena::scena()
{
    isPointSelected = NULL;
    cursor_chose = no_target;
    connect(&so, SIGNAL(situation(vector<int>)), this, SLOT(draw_so(vector<int>a)));
}

scena::scena(QGraphicsView *parent)
{
    myView = parent;
    isPointSelected = NULL;
     cursor_chose = no_target;
     connect(&so, SIGNAL(situation(int,vector<int>)), this, SLOT(genCh(int, vector<int>)));
     connect(&genA, SIGNAL(changed(int, vector<int>)), this, SLOT(genCh(int, vector<int>)));
}

void scena::addAnealing(vector<int> a)
{
    //toAnnealing.push_back(a);
    sleep(3);
    draw_so(a);
}

void scena::plusLine(point* from, point* to)
{   
    if(from == to)
        return;
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

    from->my_lines.push_back(dynamic_cast<QGraphicsLineItem*>(o));
    to->my_lines.push_back(dynamic_cast<QGraphicsLineItem*>(o));


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

    for(int i = 0; i < points.size(); i++)
        points[i]->setNum(i);

}

void scena::reDrawLines()
{
    return;
    for(int i = 0; i < lines.size(); i++)
    {
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

void scena::set_matrix(double value, point *&a, point *&b, line_item* _child)
{
    matrix[get_num(a)][get_num(b)] = value;
    matrix[get_num(b)][get_num(a)] = value;

    _child->my_text->setPlainText(QString::number(matrix[get_num(a)][get_num(b)]));
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
    if(!dijkstra_lines.empty()){
        foreach(auto dline, dijkstra_lines){
            this->removeItem(dline);
            delete dline;
        }
        dijkstra_lines.clear();
        foreach(auto p, points){
            if(p->isSelected()){
                p->setSelected(false);
                break;
            }
        }
    }
    QTransform trans;
    point* tmp = dynamic_cast<point*>(itemAt(event->scenePos(), trans));

    switch(cursor_chose)
    {
    case add_point:

        addPoints(event->scenePos());
        break;

    case no_target:

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
                    minusLine(lines[i]);

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
    foreach(auto this_item, this->items()){
        this->removeItem(this_item);
        delete this_item;
    }

    points.clear();
    matrix.clear();
    lines.clear();
    dijkstra_lines.clear();
    isPointSelected = NULL;
}

void scena::dia()
{
    int komp = sv.komponent_svyaznost(points,matrix);
    if(komp > 1){
        QMessageBox* box= new QMessageBox("Alert","there is " + QString::number(komp) + " graphov",
                                          QMessageBox::Information, NULL, NULL, QMessageBox::Cancel | QMessageBox::Escape);
        box->exec();
        return;
    }
    QVector<int> r = _d.dmtr(points, matrix);
    drawWay(r[0],r[1], alh.A_star(r[0],r[1],points,matrix));
    QString mfk = "Diametr = " + QString::number(r[2]);
    emit send_to_timeout_text(mfk, 5000);
}

void scena::drawLoops()
{
    if(!dijkstra_lines.empty()){
        foreach(auto d, dijkstra_lines){
            this->removeItem(d);
            delete d;
        }
        dijkstra_lines.clear();
    }
    if(points.empty())
        return;
    QVector<int> minelay = alh.DFS(points,matrix);

    QVector<QColor>colors;

    colors.push_back(Qt::green);
    colors.push_back(Qt::magenta);
    colors.push_back(Qt::cyan);
    colors.push_back(Qt::blue);
    colors.push_back(Qt::yellow);

    QColor color = colors[ rand() % colors.size() ];

    int count = 0;

    srand(time(NULL));

    for(int i = 0; i < minelay.size() - 1; i++)
    {
        if(minelay[i] != -1 && minelay[i+1] != -1){
            QLineF line(points[minelay[i]]->scenePos(), points[minelay[i+1]]->scenePos());
            QPen pen;
            pen.setWidth(6);
            pen.setColor(color);
            dijkstra_lines.push_back(addLine(line,pen));
        }
        if(minelay[i] == -1){
            color = colors[ rand() % colors.size() ];
            count++;
        }
    }
    QString toText = "is " + QString::number(count) + " loop's";
    my_bar->setTimeoutText(toText, 5000);
}
void scena::drawAint(vector<int> mas, bool kit)
{
    set<pair<int,int>>dab;
    for(int i = 0; i < mas.size() - 1;i++)
    {
        if((dab.find(make_pair(mas[i],mas[i+1])) != dab.end() ) || (dab.find(make_pair(mas[i+1],mas[i])) != dab.end())){
            QLineF line(points[mas[i]]->scenePos(),
                    points[mas[i+1]]->scenePos());
            dab.insert(make_pair(mas[i],mas[i+1]));
            dab.insert(make_pair(mas[i+1],mas[i]));
            QPen pen;
            pen.setWidth(3);
            pen.setColor(Qt::blue);
         //   QGraphicsEllipseItem *ellipse = this->addEllipse();
            dijkstra_lines.push_back(addLine(line,pen));
        }
        else{
            QLineF line(points[mas[i]]->scenePos(), points[mas[i+1]]->scenePos());
            dab.insert(make_pair(mas[i],mas[i+1]));
            dab.insert(make_pair(mas[i+1],mas[i]));
            QPen pen;
            pen.setWidth(8);
            pen.setColor(Qt::green);
            dijkstra_lines.push_back(addLine(line,pen));
        }
       if(kit)
        sleep(400);
    }
}

void scena::drawWay(int start, int end, QVector<int> way)
{
    double _rslt = 0;
    while(end != start){
        QLineF line(points[end]->scenePos(), points[way[end]]->scenePos());
        _rslt += matrix[end][way[end]];
        QPen pen;
        pen.setWidth(8);
        pen.setColor(Qt::green);
        dijkstra_lines.push_back(addLine(line,pen));
        end = way[end];
    }
    QString _aaaaa = "path is " + QString::number(_rslt);
    my_bar->setTimeoutText(_aaaaa, 4000);
}

void scena::minusLine(int a, int i)
{

        matrix[i][a] = 0;
        matrix[a][i] = 0;

}

void scena::minusLine(line_item *line)
{
    line->p_1->remove_at_lines(dynamic_cast<QGraphicsLineItem*>(line));
    line->p_2->remove_at_lines(dynamic_cast<QGraphicsLineItem*>(line));
    minusLine(get_num(line->p_1), get_num(line->p_2));
    this->removeItem(line->my_text);
    this->removeItem(line);
    for(int i = 0; i < points.size(); i++)
        points[i]->setNum(i);
    for(int i = 0; i < lines.size(); i++)
        if(lines[i] == line){
            lines.removeAt(i);
            delete line;
            return;
        }
}

void scena::removePoint(point* my_p)
{
    int n = get_num(my_p);

    foreach(auto line, my_p->my_lines){
        line_item* currentItem = dynamic_cast<line_item*>(line);
        point* sec_p = (currentItem->p_1 == my_p) ? currentItem->p_2 : currentItem->p_1;
        sec_p->remove_at_lines(line);
        this->removeItem(line);
        for(int i = 0; i < lines.size() ; i++)
            if(lines[i] == currentItem){
                lines.removeAt(i);
                break;
            }
        delete currentItem;
    }

    this->removeItem(my_p);
    delete my_p;

    for(int i = 0; i < matrix.size() ; i++)
    {
        matrix[i].removeAt(n);
    }
    matrix.removeAt(n);
    points.removeAt(n);

    for(int i = 0; i < points.size(); i++)
        points[i]->setNum(i);

}

void scena::setCursorState(int m)
{
  cursor_chose = static_cast<cursorState>(m);
}

void scena::point_move(point *this_point, QPointF position)
{

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
        isPointSelected = this_point;
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
    }
    if(cursor_chose == no_target){
        int stepen = 0;
        int n = get_num(this_point);
        for(int i = 0; i < points.size() ; i++)
            if(matrix[n][i] > 0)
                stepen++;
        QString f = "Chosed " + QString::number(get_num(this_point)) +
                " point , pos = x:" +
                QString::number(this_point->scenePos().x()) + " y:" +
                QString::number(this_point->scenePos().y()) + " pow = " + QString::number(stepen) +
                " svuaz = " +QString::number(sv.komponent_svyaznost(points,matrix));
        emit send_to_permament_status(f);
    }
    return;
}

void scena::aintAlgor(int aints, int elitem, int alpha, int betta, int iterations)
{
    if(points.empty())
        return;
    if(!dijkstra_lines.empty()){
        foreach(auto dline, dijkstra_lines){
            this->removeItem(dline);
            delete dline;
        }
        dijkstra_lines.clear();
        foreach(auto p, points){
            if(p->isSelected()){
                p->setSelected(false);
                break;
            }
        }
    }
    //draw_so(classAintVar.path(points,matrix,alpha,betta,aints,elitem,iterations));
    vector<int>reshak = classAintVar.path(points,matrix,alpha,betta,aints,elitem,iterations);
    if(reshak.size() != points.size()){
        QMessageBox* box= new QMessageBox("Alert","Need more iterations", QMessageBox::Information, NULL, NULL, QMessageBox::Cancel | QMessageBox::Escape);
          box->exec();
        return;
    }
    drawAint(reshak,false);
}

void scena::chinaa()
{

    vector<int>answer = kitaets.answerAtQuestion(points.size(),matrix);

     QDialog* local_help = new QDialog();
     local_help->setModal(true);
     local_help->setWindowTitle("Output");
     QFormLayout* grid1 = new QFormLayout();
    QPushButton *but = new QPushButton("Save");


    drawAint(answer,true);

    QLabel *ly = new QLabel;

    for(int i = 0; i < answer.size(); i++)
        ly->setText(ly->text() + " " + QString::number(answer[i]));
    whatToSaveDONTTOUCH = ly->text();
    connect(but,SIGNAL(clicked()), this, SLOT(saveChina()));
    connect(but, SIGNAL(clicked()), local_help, SLOT(close()));
    grid1->addWidget(ly);
    grid1->addWidget(but);

    local_help->setLayout(grid1);
    local_help->setFixedSize(grid1->sizeHint());
    local_help->show();
    local_help->exec();

}

void scena::saveChina()
{
    QString path = QFileDialog::getSaveFileName();
    ofstream outfile;
    outfile.open(path.toStdString() +  ".txt");
    if(!outfile.is_open()){
        QMessageBox* box= new QMessageBox("Alert","There is no saved file in main directory", QMessageBox::Information, NULL, NULL, QMessageBox::Cancel | QMessageBox::Escape);
        box->exec();
        return;
    }

    outfile << whatToSaveDONTTOUCH.toStdString();
    return;

}

void scena::salesman_porblem_replaces()///////////////////////////////////////////////////////////////////////////////////////
{
    if(points.empty())
        return;
    if(!dijkstra_lines.empty()){
        foreach(auto dline, dijkstra_lines){
            this->removeItem(dline);
            delete dline;
        }
        dijkstra_lines.clear();
        foreach(auto p, points){
            if(p->isSelected()){
                p->setSelected(false);
                break;
            }
        }
    }
    if(points.size() > 7){
         QMessageBox* box= new QMessageBox("Alert","Too many Verticles", QMessageBox::Information, NULL, NULL, QMessageBox::Cancel | QMessageBox::Escape);
           box->exec();
         return;
    }
    draw_so(sale_man.sales_man(points, matrix));

}

void scena::genetic(int itera, int n)
{
    if(points.empty()){
        return;

    }
    if(!dijkstra_lines.empty()){
        foreach(auto dline, dijkstra_lines){
            this->removeItem(dline);
            delete dline;
        }
        dijkstra_lines.clear();
        foreach(auto p, points){
            if(p->isSelected()){
                p->setSelected(false);
                break;
            }
        }
    }

    draw_so(genA.genetic(points,matrix,itera, n));
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

void scena::draw_so(vector<int> s)
{
//    for(int i = 0; i < lines.size() ; i++)
//    {
//        this->removeItem(lines[i]);
//    }
//    for(int i = 0; i < matrix.size() ; i++)
//    {
//        for(int j = 0; j < matrix.size() ;j++)
//        {
//            matrix[i][j] = 0;
//        }
//    }



//    for(int i =0; i < s.size() - 1; i++)
//        this->plusLine(points[s[i]],points[s[i+1]]);
//    this->plusLine(points[s[s.size() - 1]], points[s[0]]);

//    this->myView->parentWidget()->activateWindow();

//    qDebug() << activeWindow();

    if(!dijkstra_lines.empty()){
        foreach(auto d, dijkstra_lines){
            this->removeItem(d);
            delete d;
        }
        dijkstra_lines.clear();
    }

    QPen pen;
    pen.setWidth(6);
    pen.setColor(Qt::green);

    for(int i = 0; i < s.size() - 1; i++)
    {
        QLineF line(points[s[i]]->scenePos(), points[s[i+1]]->scenePos());
        dijkstra_lines.push_back(addLine(line,pen));
    }

    QLineF line(points[s[s.size() - 1]]->scenePos(), points[s[0]]->scenePos());
    dijkstra_lines.push_back(addLine(line,pen));

    update();
    QString _str = "Path = " + QString::number(result_way(s));
    my_bar->setTimeoutText(_str, 4000);
}

void scena::annealing_slot(int iterations)
{

    if(points.empty())
        return;
    if(!dijkstra_lines.empty()){
        foreach(auto dline, dijkstra_lines){
            this->removeItem(dline);
            delete dline;
        }
        dijkstra_lines.clear();
        foreach(auto p, points){
            if(p->isSelected()){
                p->setSelected(false);
                break;
            }
        }
    }

    vector<int>y = so.get_result(points, matrix, iterations);

//    for(int i = 0; i < toAnnealing.size(); i++)
//    {
//        draw_so(toAnnealing[i]);
//        sleep(10);
//        update();
//    }
    toAnnealing.clear();
    draw_so(y);
   // disconnect(&so, SIGNAL(situation(vector<int>)), this, SLOT(draw_so(vector<int>)));
    qDebug() << matrix;
   // vector<int> _t = ostov.get_ostov(points,matrix);

   // int y = 0;

}

void scena::setBar(status_bar *bar)
{
    my_bar = bar;
}

double scena::result_way(vector<int> path)
{
    double result = 0;
    for(int i = 0; i < points.size() - 1; i++)
    {
        result += sqrt( pow( points[path[i+1]]->scenePos().x() - points[path[i]]->scenePos().x() ,2) +
                        pow( points[path[i+1]]->scenePos().y() - points[path[i]]->scenePos().y() ,2) );
    }
    return result;
}

void scena::ostovVoid()
{
    if(points.empty())
        return;
    if(!dijkstra_lines.empty()){
        foreach(auto dline, dijkstra_lines){
            this->removeItem(dline);
            delete dline;
        }
        dijkstra_lines.clear();
        foreach(auto p, points){
            if(p->isSelected()){
                p->setSelected(false);
                break;
            }
        }
    }
    vector<int> way__ = ostov.get_ostov(points,matrix);

    for(int i = 0; i < way__.size() - 1; i+=2 ){
        QLineF line(points[way__[i]]->scenePos(),points[way__[i+1]]->scenePos());
        QPen pen;
        pen.setWidth(6);
        pen.setColor(Qt::green);
        dijkstra_lines.push_back(addLine(line,pen));
    }

}
