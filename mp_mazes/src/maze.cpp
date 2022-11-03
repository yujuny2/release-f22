/* Your code here! */
#include "maze.h"
#include <experimental/random>
#include <queue>
#include <algorithm>
#include <iostream>

SquareMaze::SquareMaze() {}

bool SquareMaze::canTravel(int x, int y, int dir) const {
    if (dir == 0 && (x + 1 >= width_ || right_[y*width_ + x])) return false;
    if (dir == 1 && (y + 1 >= height_ || down_[y*width_ + x])) return false;
    if (dir == 2 && (x - 1 < 0 || right_[y*width_ + (x-1)])) return false;
    if (dir == 3 && (y - 1 < 0 || down_[(y-1)*width_ + x])) return false;
    return true;
}

PNG* SquareMaze::drawMaze() const {
    PNG* png = new PNG(width_*10+1, height_*10+1);

    for (int i = 0; i < height_*10+1; i++) {
        png->getPixel(0, i).l = 0;
    }

    for (int i = 0; i < width_*10+1; i++) {
        if (i >= 1 && i <= 9) continue;
        png->getPixel(i, 0).l = 0;
    }

    for (int i = 0; i < width_*height_; i++) {
        if (right_[i]) {
            for (int k = 0; k <= 10; k++) 
                png->getPixel((i%width_+1)*10, (i/width_)*10+k).l = 0;
        }
        if (down_[i]) {
            for (int k = 0; k <= 10; k++) 
                png->getPixel((i%width_)*10+k, (i/width_+1)*10).l = 0;
        }
    }

    return png;
}

PNG* SquareMaze::drawMazeWithSolution() {
    PNG* png = drawMaze();
    std::vector<int> solution = solveMaze();

    int x = 5;
    int y = 5;

    for (unsigned i = 0; i < solution.size(); i++) {
        if (solution[i] == 0) {
            for (int k = 0; k < 11; k++) {
                HSLAPixel pixel(0,1,0.5,1);
                png->getPixel(x+k, y) = pixel;
            }
            x += 10;
        } else if (solution[i] == 1) {
            for (int k = 0; k < 11; k++) {
                HSLAPixel pixel(0,1,0.5,1);
                png->getPixel(x, y+k) = pixel;
            }
            y += 10;
        } else if (solution[i] == 2) {
            for (int k = 0; k < 11; k++) {
                HSLAPixel pixel(0,1,0.5,1);
                png->getPixel(x-k, y) = pixel;
            }
            x -= 10;
        } else if (solution[i] == 3) {
            for (int k = 0; k < 11; k++) {
                HSLAPixel pixel(0,1,0.5,1);
                png->getPixel(x, y-k) = pixel;
            }
            y -= 10;
        }
    }

    int exit_y = y + 5;
    int exit_x = x - 5;
    for (int k = 1; k < 10; k++) {
        png->getPixel(exit_x+k, exit_y).l = 1;
    }

    return png;
}

void SquareMaze::makeMaze(int width, int height) {
    if (!dsets_.empty()) {
        dsets_.clear();
    }

    width_ = width;
    height_ = height;
    dsets_.addelements(width*height);

    right_.clear();
    down_.clear();

    right_.resize(width*height);
    down_.resize(width*height);
    for (unsigned i = 0; i < right_.size(); i++) {
        right_[i] = true;
        down_[i] = true;
    }

    while (dsets_.number_of_sets() > 1) {
        // 0 = right; 1 = down; 2 = left; 3 = up
        int elem = std::experimental::randint(0, width*height-1);

        std::vector<int> directions;
        // check right wall and the right element is not in the same set
        if (!((elem + 1) % width == 0) && dsets_.find(elem) != dsets_.find(elem + 1)) {
            directions.push_back(0);
        }
        // check down wall and the down element is not in the same set
        if (!(elem >= (width * (height - 1))) && dsets_.find(elem) != dsets_.find(elem + width)) {
            directions.push_back(1);
        }
        // check left wall and the left element is not in the same set
        if (!(elem % width == 0) && dsets_.find(elem) != dsets_.find(elem - 1)) {
            directions.push_back(2);
        }
        // check up wall and the up element is not in the same set
        if (!(elem < width) && dsets_.find(elem) != dsets_.find(elem - width)) {
            directions.push_back(3);
        }

        if (directions.size() == 0) continue;
        int dir = directions[std::experimental::randint(0,int(directions.size())-1)];

        int adj_elem;
        switch (dir) {
            case 0:
                adj_elem = elem + 1;
                break;
            case 1:
                adj_elem = elem + width;
                break;
            case 2:
                adj_elem = elem - 1;
                break;
            case 3:
                adj_elem = elem - width;
                break; 
        }
        dsets_.setunion(elem, adj_elem);
        setWall(elem%width, elem/width, dir, false);
    }
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
    switch (dir) {
        case 0:
            right_[y*width_+x] = exists;
            break;
        case 1:
            down_[y*width_+x] = exists;
            break;
        case 2:
            right_[y*width_+x-1] = exists;
            break;
        case 3:
            down_[(y-1)*width_+x] = exists;
            break; 
    }
}

std::vector<int> SquareMaze::solveMaze() {
    std::vector<bool> visited(width_*height_, false);
    std::vector<int> path(width_*height_, 0);
    std::queue<int> queue;

    visited[0] = true;
    queue.push(0);

    while (!queue.empty()) {
        int v = queue.front();
        queue.pop();
        
        int right = v + 1;
        int down = v + width_;
        int left = v - 1;
        int up = v - width_;

        // x(col) = dir%width_; y(row) = dir/width_
        // 0 = right; 1 = down; 2 = left; 3 = up
        if (canTravel(v%width_, v/width_, 0) && !visited[right]) {
            queue.push(right);
            visited[right] = true;
            path[right] = path[v] + 1;
        }
        if (canTravel(v%width_, v/width_, 1) && !visited[down]) {
            queue.push(down);
            visited[down] = true;
            path[down] = path[v] + 1;
        }
        if (canTravel(v%width_, v/width_, 2) && !visited[left]) {
            queue.push(left);
            visited[left] = true;
            path[left] = path[v] + 1;
        }
        if (canTravel(v%width_, v/width_, 3) && !visited[up]) {
            queue.push(up);
            visited[up] = true;
            path[up] = path[v] + 1;
        }
    }

    // get exit with the maximum path length
    int max_index = 0;
    for (int i = width_*(height_-1); i < width_*height_; i++) {
        if (path[i] > path[max_index]) max_index = i;
    }
    
    std::vector<int> solution;
    int current_index = max_index;
    while (path[current_index] != 0) {
        int right = current_index + 1;
        int down = current_index + width_;
        int left = current_index - 1;
        int up = current_index - width_;

        int next_step = path[current_index] - 1;
        if (canTravel(current_index%width_, current_index/width_, 0) && path[right] == next_step) {
            solution.push_back(2);
            current_index = right;
        } else if (canTravel(current_index%width_, current_index/width_, 1) && path[down] == next_step) {
            solution.push_back(3);
            current_index = down;
        } else if (canTravel(current_index%width_, current_index/width_, 2) && path[left] == next_step) {
            solution.push_back(0);
            current_index = left;
        } else if (canTravel(current_index%width_, current_index/width_, 3) && path[up] == next_step) {
            solution.push_back(1);
            current_index = up;
        }
    }

    std::reverse(solution.begin(), solution.end());
    return solution;
}