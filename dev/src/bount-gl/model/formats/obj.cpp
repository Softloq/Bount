#include "bount-lib/gl/precompiled.hpp"
#include "bount-gl/model/formats/obj.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

namespace bount::gl::model::format
{
    obj_file_res::obj_file_res(const string& path)
    {
        std::ifstream f(path);
        if (!f.is_open()) return;
        
        string line;
        while (std::getline(f, line))
        {   // Parses each line of the file.
            if (std::stringstream ss(line); ss >> std::ws && !ss.eof())
            {   // Starts the check after skipping leading spaces.
                const char c = ss.peek();
                switch (c)
                {
                // Comment
                case '#': {
                    ss.seekg(0, std::ios::end);
                    break;
                }
                // Vertex
                case 'v': {
                    string type;
                    ss >> type;
                    if ("v" == type)
                    {   // Stores geometric vertex
                        float32 x, y, z, w;
                        ss >> x >> y >> z >> std::ws;
                        if (!ss.eof()) { ss >> w; }
                        else w = 1.0f;
                        this->m_vertices.push_back({x, y, z, w});
                    }
                    else if ("vt" == type)
                    {
                        string error = string("Not supported yet: ") + line;
                        std::cerr << error << std::endl;
                        throw std::exception(error.c_str());
                    }
                    else if ("vn" == type)
                    {
                        string error = string("Not supported yet: ") + line;
                        std::cerr << error << std::endl;
                        throw std::exception(error.c_str());
                    }
                    else if ("vp" == type)
                    {
                        string error = string("Not supported yet: ") + line;
                        std::cerr << error << std::endl;
                        throw std::exception(error.c_str());
                    }
                    else
                    {
                        string error = string("Not supported: ") + line;
                        std::cerr << error << std::endl;
                        throw std::exception(error.c_str());
                    }
                    break;
                }
                // Face
                case 'f': {
                    string error = string("Not supported yet: ") + line;
                    std::cerr << error << std::endl;
                    throw std::exception(error.c_str());
                    break;
                }
                // Line
                case 'l': {
                    string error = string("Not supported yet: ") + line;
                    std::cerr << error << std::endl;
                    throw std::exception(error.c_str());
                    break;
                }
                // Named Object
                case 'o': {
                    string error = string("Not supported yet: ") + line;
                    std::cerr << error << std::endl;
                    throw std::exception(error.c_str());
                    break;
                }
                // Named Group
                case 'g': {
                    string error = string("Not supported yet: ") + line;
                    std::cerr << error << std::endl;
                    throw std::exception(error.c_str());
                    break;
                }
                default: {
                    string error = string("Not supported: ") + line;
                    std::cerr << error << std::endl;
                    throw std::exception(error.c_str());
                    break;
                }
                }
            }
        }
    }

    obj_text_res::obj_text_res(const string& text)
    {

    }

    obj::obj(const obj_res_interface& res)
    {

    }
}