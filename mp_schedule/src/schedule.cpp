/**
 * @file schedule.cpp
 * Exam scheduling using graph coloring
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <unordered_map>

#include "schedule.h"
#include "utils.h"
#include <algorithm>

/**
 * Given a filename to a CSV-formatted text file, create a 2D vector of strings where each row
 * in the text file is a row in the V2D and each comma-separated value is stripped of whitespace
 * and stored as its own string. 
 * 
 * Your V2D should match the exact structure of the input file -- so the first row, first column
 * in the original file should be the first row, first column of the V2D.
 *  
 * @param filename The filename of a CSV-formatted text file. 
 */
V2D file_to_V2D(const std::string & filename){
    // Your code here!
    // get all text data from file
    V2D data;
    std::string data_str = file_to_string(filename);

    std::vector<std::string> row_data;
    int num_rows = SplitString(data_str, '\n', row_data);

    for (int i = 0; i < num_rows; i++) {
        std::vector<std::string> data_vec;
        int num_cols = SplitString(row_data[i], ',', data_vec);
        for (int j = 0; j < num_cols; j++) {
            data_vec[j] = Trim(data_vec[j]);
        }
        data.push_back(data_vec);
    }

    return data;
}

/**
 * Given a course roster and a list of students and their courses, 
 * perform data correction and return a course roster of valid students (and only non-empty courses).
 * 
 * A 'valid student' is a student who is both in the course roster and the student's own listing contains the course
 * A course which has no students (or all students have been removed for not being valid) should be removed
 * 
 * @param cv A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param student A 2D vector of strings where each row is a student ID followed by the courses they are taking
 */
V2D clean(const V2D & cv, const V2D & student){
    // YOUR CODE HERE
    V2D cleaned_data;

    std::unordered_map<std::string, std::vector<std::string>> courses;
    std::unordered_map<std::string, std::vector<std::string>> students;
    std::unordered_map<std::string, std::vector<std::string>> roster;
    std::vector<std::string> order;

    // get courses map
    for (unsigned i = 0; i < cv.size(); i++) {
        std::vector<std::string> c = cv[i];
        std::string course_name = c[0];
        std::vector<std::string> students_name = {c.begin() + 1, c.end()};
        courses[course_name] = students_name;
        order.push_back(course_name);
    }

    // get students map
    for (unsigned i = 0; i < student.size(); i++) {
        std::vector<std::string> s = student[i];
        std::string student_name = s[0];
        std::vector<std::string> courses_name = {s.begin() + 1, s.end()};
        students[student_name] = courses_name;
    }

    // check courses map
    for (std::pair<std::string, std::vector<std::string>> key_val : courses) {
        roster[key_val.first] = {key_val.first};

        for (unsigned j = 0; j < key_val.second.size(); j++) { // loop through students in a course
            std::vector<std::string> c = students[key_val.second[j]];
            if (std::find(c.begin(), c.end(), key_val.first) != c.end()) {
                roster[key_val.first].push_back(key_val.second[j]);
            }
        }
    }

    for (unsigned i = 0; i < order.size(); i++) {
        if (roster[order[i]].size() > 1) {
            cleaned_data.push_back(roster[order[i]]);
        }
    }

    return cleaned_data;
}

/**
 * Given a collection of courses and a list of available times, create a valid scheduling (if possible).
 * 
 * A 'valid schedule' should assign each course to a timeslot in such a way that there are no conflicts for exams
 * In other words, two courses who share a student should not share an exam time.
 * Your solution should try to minimize the total number of timeslots but should not exceed the timeslots given.
 * 
 * The output V2D should have one row for each timeslot, even if that timeslot is not used.
 * 
 * As the problem is NP-complete, your first scheduling might not result in a valid match. Your solution should 
 * continue to attempt different schedulings until 1) a valid scheduling is found or 2) you have exhausted all possible
 * starting positions. If no match is possible, return a V2D with one row with the string '-1' as the only value. 
 * 
 * @param courses A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param timeslots A vector of strings giving the total number of unique timeslots
 */
V2D schedule(const V2D &courses, const std::vector<std::string> &timeslots){
    // Your code here!
    V2D new_schedule;
    unsigned num_courses = courses.size();

    // adjacency matrix that represents the edges
    std::vector<std::vector<bool>> edges(num_courses, std::vector<bool>(num_courses, false));

    for (unsigned i = 0; i < num_courses; i++) {
        for (unsigned j = 1; j < courses[i].size(); j++) {
            for (unsigned k = i + 1; k < num_courses; k++) {
                if (std::find(courses[k].begin(), courses[k].end(), courses[i][j]) != courses[k].end()) {
                    edges[i][k] = true;
                    edges[k][i] = true;
                }
            }
        }
    }

    // get course names
    std::vector<std::string> course_names;
    for (unsigned i = 0; i < num_courses; i++) {
        course_names.push_back(courses[i][0]);
    }

    // graph coloring
    for (unsigned i = 0; i < num_courses; i++) { // loop through each starting vertex
        std::unordered_map<int, std::vector<std::string>> map;
        map[0] = {timeslots[0], course_names[0]};
        std::vector<int> colors = {0};
        bool done = true;

        for (unsigned j = 1; j < num_courses; j++) { // loop through vertices
            int color = 0;

            std::vector<bool> available(map.size(), true);
            for (unsigned k = 0; k < j; k++) {
                if (edges[j][k]) {
                    available[colors[k]] = false;
                }
            }

            for (unsigned k = 0; k < available.size(); k++) {
                if (available[k]) {
                    color = k;
                    break;
                }
                color = map.size();
            }

            // if the number of colors is greater than the number of timeslots, go to the next option
            if (color >= int(timeslots.size())) {
                done = false;
                break;
            }

            std::unordered_map<int, std::vector<std::string>>::iterator lookup = map.find(color);
            if (lookup != map.end()) {
                map[color].push_back(course_names[j]);
            } else {
                map[color] = {timeslots[color], course_names[j]};
            }
            colors.push_back(color);
        }

        // terminate if there is valid labeling
        if (map.size() <= timeslots.size() && done) {
            for (std::pair<int, std::vector<std::string>> key_val : map) {
                new_schedule.push_back(key_val.second);
            }

            for (unsigned k = map.size(); k < timeslots.size(); k++) {
                std::vector<std::string> t = {timeslots[k]};
                new_schedule.push_back(t);
            }
            return new_schedule;
        } 

        // start from the second vertex if the current vertex fails; move the first vertex to the last
        std::rotate(course_names.begin(), course_names.begin() + 1, course_names.end());
        std::rotate(edges.begin(), edges.begin() + 1, edges.end());
        for (unsigned i = 0; i < num_courses; i++) {
            std::rotate(edges[i].begin(), edges[i].begin() + 1, edges[i].end());
        }
    }
    return {{"-1"}};
}