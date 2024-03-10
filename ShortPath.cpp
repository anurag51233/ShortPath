#include "ShortPath.h"




int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1100, 800), "Short Path!!!", sf::Style::Default, settings);
  

#pragma region TestCode

#pragma endregion


#pragma region Defines paths and lines and points

    bool bDrawLineMouse = false;
    bool bFindPath = false;
    //Contains all the path i.e. lines
    std::vector<sf::Vertex> paths;

    //a ref line when moving mouse
    sf::Vertex line[2] = {
                            sf::Vertex(sf::Vector2f(10, 10)),
                            sf::Vertex(sf::Vector2f(100, 10))
                         };

    // Set the line color (optional)
    line[0].color = sf::Color::White;
    line[1].color = sf::Color::White;



    paths.push_back(line[0]);
    paths.push_back(line[1]);

#pragma endregion


#pragma region Defines for scanning path
    sf::Image winimage;
    sf::Texture wintexture;

    bool bShowNode = false;
    bool bStruckNode = false;
    int tracetime = 0;


    std::vector<sf::Vertex> debugPoints;

    //for first and last node tracing
    std::vector<sf::Vertex> tracecircle;
    
    //for middle nodes tracing
    std::vector<sf::Vertex> tracepoints;

    //two circle points 
    sf::Vertex point[2];

    //for poping out one direction at time for trace until head and tailnode gets valid number
    my::TracePath pathsForTracing;  //stack
    //later is added to allpath
    my::TracePath tempPathTracing;
    //if a path is traced then it is added to all path
    std::vector<my::TracePath> allpaths;

    bool bScanDiversion = true;

    my::PathNode pathNode;

    sf::CircleShape circlepoint1(8.f);
    sf::CircleShape circlepoint2(8.f);
    circlepoint1.setFillColor(sf::Color(0, 250, 0));
    circlepoint2.setFillColor(sf::Color(0, 250, 0));
#pragma endregion


#pragma region Text&font Code
    sf::Font font;
    if (!font.loadFromFile("res/Fonts/Banana.ttf"))
    {
        std::cout << "font was not loaded " << std::endl;
        window.close();
    }

    sf::Text* text = new sf::Text();
    sf::Text* xtext = new sf::Text("x",font,20);
    sf::Text* ytext = new sf::Text("y", font, 20);
    text->setFont(font);
    text->setString("press 'F' for finding path");
    text->setCharacterSize(24);
    text->setFillColor(sf::Color::White);
    text->setPosition(sf::Vector2f(100,10));

    xtext->setFillColor(sf::Color::White);
    ytext->setFillColor(sf::Color::White);
    xtext->setPosition(sf::Vector2f(600, 10));
    ytext->setPosition(sf::Vector2f(700, 10));




#pragma endregion



    //////------handling events and draw class--------///////

    while (window.isOpen())
    {


        ///------Event Handling------///
        sf::Event event;
        while (window.pollEvent(event))
        {

#pragma region DefaultEvent

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::Resized)
            {
                std::cout << "Do not resize the windows " << std::endl;
                std::cout << "new width: " << event.size.width << std::endl;
                std::cout << "new height: " << event.size.height << std::endl;
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    std::cout << "the escape key was pressed" << std::endl;
                    std::cout << "scancode: " << event.key.code << std::endl;
                    std::cout << "code: " << event.key.code << std::endl;
                    std::cout << "control: " << event.key.control << std::endl;
                    std::cout << "alt: " << event.key.alt << std::endl;
                    std::cout << "shift: " << event.key.shift << std::endl;
                    std::cout << "system: " << event.key.system << std::endl;
                    window.close();
                }
            }

#pragma endregion


#pragma region Handling Events for Creating paths 
            // For drawing paths and getting the point from the user 
            // winimage is updated to have 


            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::F)
                {
                    bFindPath = true;
                    line[0].color = sf::Color::Red;
                    line[1].color = sf::Color::Red;
                }
            }


           
            //Draw paths 
            /// mouse movement for drawing stuffs
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    
                    bDrawLineMouse = true; 
                    line[0].position.x = event.mouseButton.x;
                    line[0].position.y = event.mouseButton.y;
                    line[1].position.x = event.mouseButton.x;
                    line[1].position.y = event.mouseButton.y;
                    if (bFindPath)
                    {
                        point[0] = line[0];
                        point[1] = line[1];
                        point[0].position.x -= 8;
                        point[0].position.y -= 8;

                        point[1].position.x -= 8;
                        point[1].position.y -= 8;

                    }
                }
            }

            if (event.type == sf::Event::MouseMoved)
            {
                xtext->setString(std::to_string(event.mouseMove.x));
                ytext->setString(std::to_string(event.mouseMove.y));
                if (bDrawLineMouse)
                {
                    line[1].position.x = event.mouseMove.x;
                    line[1].position.y = event.mouseMove.y;
                    if (bFindPath)
                    {
                        point[0] = line[0];
                        point[1] = line[1];
                        point[0].position.x -= 8;
                        point[0].position.y -= 8;

                        point[1].position.x -= 8;
                        point[1].position.y -= 8;
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    bDrawLineMouse = false;
                    if (!bFindPath)
                    {
                        AddLineToPath(paths, line,1);
                    }
                    

                }
            }

           
#pragma endregion
            
            //Finding path code
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Enter)
                {
                    
                    // Capture the window content into the texture
                    sf::Vector2u windowSize = window.getSize();
                    wintexture.create(windowSize.x, windowSize.y);
                    wintexture.update(window);
                    winimage = wintexture.copyToImage();

                    std::cout << "scanning circle" << std::endl;


#pragma region First and Last Node assignment

                    //------------Finding the first and last node ------------------
                    tracecircle.clear();
                    scanCircleBres(point[0].position.x + 8, point[0].position.y + 8, 10, tracecircle, winimage);
                    if(!tracecircle.empty())
                        combineNearbyPixels(tracecircle, 3.0f);
                    //send the circle i.e. point[0] to top as it becomes useless after taking the node
                    //added the found pos to Node 
                    //debugPoints.insert(debugPoints.end(), tracecircle.begin(), tracecircle.end());

                    if (!tracecircle.empty())
                    {
                        pathNode.AddPathNode(tracecircle[0].position);
                        point[0].position.x = 100;
                        point[0].position.y = 100;
                    }

                    tracecircle.clear();
                    scanCircleBres(point[1].position.x + 8, point[1].position.y + 8, 10, tracecircle, winimage);
                    if (!tracecircle.empty())
                        combineNearbyPixels(tracecircle, 3.0f);
                    //send the circle i.e. point[0] to top as it becomes useless after taking the node
                    //added the found pos to Node 
                    if (!tracecircle.empty())
                    {
                        pathNode.AddPathNode(tracecircle[0].position);
                        point[1].position.x = 100;
                        point[1].position.y = 100;

                    }
                    ///------------End  Finding the first and last node -----------------------
#pragma endregion
                    
                    //staring from first node 
                    tracepoints.clear();

                    scanCircleBres(pathNode.pathNodes[0].pos.x, pathNode.pathNodes[0].pos.y, 20, tracepoints, winimage);
                    //DebugscanCircleBres(pathNode.pathNodes[0].pos.x, pathNode.pathNodes[0].pos.y, 5, debugPoints, winimage);
                    
                    
                    combineNearbyPixels(tracepoints, 3.0f);
                    FilterLinesFromTracePoints(tracepoints, pathNode.pathNodes[0].pos, winimage);
                    
                    debugPoints.insert(debugPoints.end(),tracepoints.begin(), tracepoints.end());

                    for (size_t i = 0; i < tracepoints.size(); i++)
                    {

                        std::cout << "tracepointes are  " << tracepoints[i].position.x << std::endl;

                        my::Direction tempdir;
                        tempdir.head = tracepoints[i].position;
                        tempdir.tail = pathNode.pathNodes[0].pos;
                        tempdir.headNode = -1;
                        tempdir.tailNode = 0;
                        pathsForTracing.AddPath(tempdir);
                        
                    }
                }

                if (event.key.code == sf::Keyboard::S)
                {
                    bShowNode = bShowNode ? false : true;
                }

                if (event.key.code == sf::Keyboard::P)
                {
                    /// ======= pop out pathsForTracing to trace it tempPathTracing ---> allpath =======
                newtrace:                    
                    if(!pathsForTracing.paths.empty())
                    {

                        tempPathTracing.AddPath(pathsForTracing.paths.back());
                        pathsForTracing.paths.pop_back();
                        std::cout << "picked a node" << std::endl;
                    }
                }





            endofT:
                ///----------middle nodes path tracing -------------
                if (event.key.code == sf::Keyboard::T)
                {
                    sf::Vector2u windowSize = window.getSize();
                    wintexture.create(windowSize.x, windowSize.y);
                    wintexture.update(window);
                    winimage = wintexture.copyToImage();

                    std::cout << "pressed t" << std::endl;
                    for (size_t i = 0; i < pathsForTracing.paths.size(); i++)
                    {
                        std::cout << " path for tracing : " << pathsForTracing.paths[i].head.x << " " << pathsForTracing.paths[i].head.y << std::endl;
                    }


                    
                    if (tempPathTracing.paths.size() == 0) { goto endofT; }
                    //scan for the tracepoints.back().head
                    tracepoints.clear();
                    scanCircleBres(tempPathTracing.paths.back().head.x, tempPathTracing.paths.back().head.y, 20.0f, tracepoints, winimage);
                    
                    //DebugscanCircleBres(pathNode.pathNodes[0].pos.x, pathNode.pathNodes[0].pos.y, 5, debugPoints, winimage);
                    combineNearbyPixels(tracepoints, 4.0f);

                    FilterLinesFromTracePoints(tracepoints, tempPathTracing.paths.back().head, winimage);
                    



                    int distanceClampTracePoints;
                    for (int i = 0; i < tracepoints.size(); i++)
                    {
                        distanceClampTracePoints = distanceOfVector(tracepoints[i].position, tempPathTracing.paths.back().tail);
                        if (distanceClampTracePoints < 20.0f)
                        {

                            // Get iterator to the element at the specified index
                            auto it = tracepoints.begin() + i;
                            // Erase the element using the iterator
                            tracepoints.erase(it);


                        }
                    }


                   
                        //if node is struct
                        if (!tracepoints.empty())
                        {
                            int structNodenum = -1;

                            std::cout << "struct the node !!! " << tracepoints.back().position.x << " " << tracepoints.back().position.y << std::endl;
                            structNodenum = FindNodeCloseToPoint(pathNode.pathNodes[1] , tracepoints.back().position);

                            if (structNodenum != -1)
                            {

                                //update node of tempPathTracing
                                for (int i = 0; i < tempPathTracing.paths.size(); i++)
                                {
                                    tempPathTracing.paths[i].headNode = structNodenum;

                                }

                                allpaths.push_back(tempPathTracing);
                                tempPathTracing.paths.clear();

                                goto newtrace;

                            }
                        }
                    





                    if (tracepoints.size() == 1)
                    {
                        int tailNodenum = tempPathTracing.paths.back().tailNode;
                        tempPathTracing.AddPath(my::Direction(tracepoints.back().position, tempPathTracing.paths.back().head));
                        tempPathTracing.paths.back().tailNode = tailNodenum;
                        bScanDiversion = true;

                    }
                    else if (tracepoints.size() >= 1)
                    {
                        bScanDiversion = true;
                        pathNode.AddPathNode(tempPathTracing.paths.back().head);
                        int nodeNumber = pathNode.pathNodes.size()-1;


                        //update node of tempPathTracing
                        for (int i = 0; i < tempPathTracing.paths.size(); i++)
                        {
                            tempPathTracing.paths[i].headNode = nodeNumber;

                        }

                        allpaths.push_back(tempPathTracing);


                        // add the node trace to pathForTracing
                        tracepoints.clear();

                        scanCircleBres(pathNode.pathNodes.back().pos.x, pathNode.pathNodes.back().pos.y, 20, tracepoints, winimage);
                        //DebugscanCircleBres(pathNode.pathNodes[0].pos.x, pathNode.pathNodes[0].pos.y, 5, debugPoints, winimage);


                        combineNearbyPixels(tracepoints, 3.0f);
                        FilterLinesFromTracePoints(tracepoints, pathNode.pathNodes.back().pos, winimage);
                        int distanceClampTracePoints;
                        for (int i = 0; i < tracepoints.size(); i++)
                        {
                            distanceClampTracePoints = distanceOfVector(tracepoints[i].position, tempPathTracing.paths.back().tail);
                            if (distanceClampTracePoints < 10.0f)
                            {

                                // Get iterator to the element at the specified index
                                auto it = tracepoints.begin() + i;
                                // Erase the element using the iterator
                                tracepoints.erase(it);


                            }
                        }




                        for (size_t i = 0; i < tracepoints.size(); i++)
                        {

                            std::cout << "tracepointes are  " << tracepoints[i].position.x << std::endl;

                            my::Direction tempdir;
                            tempdir.head = tracepoints[i].position;
                            tempdir.tail = pathNode.pathNodes.back().pos;
                            tempdir.headNode = -1;
                            tempdir.tailNode = pathNode.pathNodes.size() - 1;
                            pathsForTracing.AddPath(tempdir);

                        }


                        tempPathTracing.paths.clear();

                        if (!pathsForTracing.paths.empty())
                        {

                            tempPathTracing.AddPath(pathsForTracing.paths.back());
                            pathsForTracing.paths.pop_back();
                            std::cout << "picked a node" << std::endl;
                        }

                    }
                    else if (tracepoints.size() < 1 && bScanDiversion)
                    {
                        std::cout << "no multiple tracepont error" << std::endl;

                        auto nextPoint = scanNextWalkPoint(my::Direction(tempPathTracing.paths.back().head, tempPathTracing.paths.back().tail), winimage, window);
                        
                        int tailNodenum = tempPathTracing.paths.back().tailNode;
                        tempPathTracing.AddPath(my::Direction(nextPoint, tempPathTracing.paths.back().head));
                        tempPathTracing.paths.back().tailNode = tailNodenum;
                        bScanDiversion = false;
                        //tracepoints.clear();
                        //scanCircleBres(tempPathTracing.paths.back().head.x, tempPathTracing.paths.back().head.y, 5, tracepoints, winimage);
                        ////DebugscanCircleBres(pathNode.pathNodes[0].pos.x, pathNode.pathNodes[0].pos.y, 5, debugPoints, winimage);
                        //combineNearbyPixels(tracepoints, 3.0f);
                        //FilterLinesFromTracePoints(tracepoints, tempPathTracing.paths.back().head, winimage);
                    }

                    //if (tracepoints.size() >= 1)
                    //{
                    //    /*sf::Vector2f direction(tracepoints[0].position - tempPathTracing.paths.back().head);
                    //    direction = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);*/
                    //    auto nextPoint = scanNextWalkPoint(my::Direction(tracepoints.back().position, tempPathTracing.paths.back().head), winimage, window);
                    //    int tailNodenum = tempPathTracing.paths.back().tailNode;
                    //    tempPathTracing.AddPath(my::Direction(nextPoint - ((nextPoint - tempPathTracing.paths.back().head)/2.0f), tempPathTracing.paths.back().head));
                    //    tempPathTracing.paths.back().tailNode = tailNodenum;
                    //}
                    //else if(tracepoints.size()>1)
                    //{
                    //    std::cout << "multiple tracepont error" << std::endl;
                    //}



                }
                

            }


           
        }







        //////----------window handling segment----------//////
        window.clear();

        window.draw(*text);
        window.draw(*xtext);
        window.draw(*ytext);

        window.draw(&paths[0], paths.size(), sf::Lines);


        pathNode.DrawPathNode(window, bShowNode);
        for (int i = 0; i < allpaths.size(); i++)
        {
            allpaths[i].DrawPath(window);
        }
        pathsForTracing.DrawPath(window);
        tempPathTracing.DrawPath(window);



        // showing lines or points when mouse is moved 
        if (bFindPath)
        {
            circlepoint1.setPosition(point[0].position);
            circlepoint2.setPosition(point[1].position);
            window.draw(circlepoint1);
            window.draw(circlepoint2);

        }
        else
        {
            window.draw(line, 2, sf::Lines);
        }
        
        //test draw
        if (!tracecircle.empty())
        {
            window.draw(&tracecircle[0], tracecircle.size(), sf::Points);
            //window.draw(&debugPoints[0], debugPoints.size(), sf::Points);
            

        }



        window.display();

        
    }

    return 0;
}




void AddLineToPath(std::vector<sf::Vertex>& paths, sf::Vertex line[2],float thickness)
{
    sf::Vector2f direction = line[1].position - line[0].position;
    sf::Vector2f normal(direction.y, -direction.x);  // Normal vector for perpendicular lines
    normal = normal / std::sqrt(normal.x * normal.x + normal.y * normal.y); // Normalize for consistent thickness

    // Create vertices for the top and bottom lines of the rectangle
    sf::Vertex topLine[] = {
        line[0].position + normal * thickness / 2.f,
        line[1].position + normal * thickness / 2.f
    };
    sf::Vertex bottomLine[] = {
        line[0].position - normal * thickness / 2.f,
        line[1].position - normal * thickness / 2.f
    };

    // Add vertices in the correct order to create a filled rectangle representing the line
    paths.push_back(topLine[0]);
    paths.push_back(topLine[1]);
    paths.push_back(bottomLine[1]);
    paths.push_back(bottomLine[0]);

}



void combineNearbyPixels(std::vector<sf::Vertex>& vec, float threshold) {
    // Resulting vector to store combined vertices
    std::vector<sf::Vertex> combinedVec;
    bool combined = false;
    float distanceLength;
    sf::Vector2f distance;

    // Iterate through the original vector
    for (size_t i = 0; i < vec.size(); ++i) {
        sf::Vertex current = vec[i];
        combined = false;

        // Iterate through subsequent vertices
        for (size_t j = i + 1; j < vec.size(); ++j) {
            distance = vec[j].position - current.position;
            distanceLength = std::sqrt(distance.x * distance.x + distance.y * distance.y);

            // Combine if within threshold distance
            if (distanceLength <= threshold) {
                // Average positions and optionally colors (if applicable)
                current.position = (current.position + vec[j].position) / 2.f;
                // ... (add color averaging logic if needed)
                combined = true;
                break;
            }
        }

        // If not combined, add to the result vector
        if (!combined) {
            combinedVec.push_back(current);
        }
    }

    // Assign the combined vector back to the original reference
    vec = combinedVec;
}

void FilterLinesFromTracePoints(std::vector<sf::Vertex>& vec, sf::Vector2f center, sf::Image winimage)
{
    sf::Vector2f distance;
    std::vector<sf::Vertex> currentvec;
    float uptolenth = 40.0f;

    sf::Vertex temp;
    for (size_t i = 0; i < vec.size(); i++)
    {
        //increment by 15 distance 
        temp = vec[i];
        distance = vec[i].position - center;
        float distanceLength = std::sqrt(distance.x * distance.x + distance.y * distance.y);
      
        sf::Vector2f unitvector = sf::Vector2f(distance.x / distanceLength, distance.y / distanceLength);
        
        temp.position =temp.position +  sf::Vector2f(unitvector.x*uptolenth, unitvector.y * uptolenth);

        //and check 
        std::cout << "scanning for lines.." << std::endl;
        if (scanNearPointPixel(temp.position,winimage))
        {
            std::cout << "got some line" << std::endl;
            currentvec.push_back(vec[i]);
        }

    }

    vec.clear();
    vec = currentvec;

}

int FindNodeCloseToPoint(my::IntersectionNode& pathNode, sf::Vector2f point)
{
    sf::Vector2f diff;
    float distance;
    
        diff.x = pathNode.pos.x - point.x;
        diff.y = pathNode.pos.y - point.y;

        distance = sqrt(diff.x * diff.x + diff.y * diff.y);
        if (distance < 30.f)
        {
            std::cout << "last node found !!!!!!!!!!!!!" << point.x <<" "<< point.y << std::endl;
            return 1;
        }
    
    return -1;
}

sf::Vector2f FindNextWalkPoint(my::Direction walkdir, sf::Image& winimage)
{
    return sf::Vector2f();
}



