////////////////////////////////////////////////////////////////////////////
// BSD 3-Clause License
//
// Copyright (c) 2024, Kyeonghyeon Baek, Sehyeon Chung, Handong Cho, 
// Hyunbae Seo, Kyu-myung Choi, and Taewhan Kim
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
//    contributors may be used to endorse or promote products derived from
//    this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
////////////////////////////////////////////////////////////////////////////

#include "../header/PlaceGrid.h"

void OutputTrans::set(std::string _name, std::string _left, std::string _gate, std::string _right, int _nfin)
{
    name = _name;
    left = _left;
    gate = _gate;
    right = _right;
    nfin = _nfin;
}

bool OutputTrans::operator==(const OutputTrans &ot) const {
    if (this->gate == ot.gate && this->left == ot.left && this->right == ot.right && this->nfin == ot.nfin)
        return true;
    else return false;
}

bool OutputTrans::operator!=(const OutputTrans &ot) const {
    if (!(*this == ot)) return true;
    else return true;
}

bool PlaceGrid::operator==(const PlaceGrid &pg) const {
    if (this->cellWidth != pg.cellWidth) return false;
    for (int i = 0; i < this->nmos.size(); i++) {
        if (this->nmos[i] != pg.nmos[i]) return false;
    }
    for (int i = 0; i < this->pmos.size(); i++) {
        if (this->pmos[i] != pg.pmos[i]) return false;
    }
    return true;
}

bool PlaceGrid::operator!=(const PlaceGrid &pg) const {
    if (!(*this == pg)) return true;
    return false;
}

void PlaceGrid::print_place (Cell& cell, fs::path outPath, int num) {

    fs::path cell_info_path = outPath / fs::path("cell_info");
    fs::path place_result_path = outPath / fs::path("place_result");

    if (num >= 0) {

        std::string cell_info_num = "cell_info_" + std::to_string(num);
        std::string place_info_num = "place_result_" + std::to_string(num);

        cell_info_path = outPath / fs::path(cell_info_num);
        place_result_path = outPath / fs::path(place_info_num);
    }

    //fs::create_directories(cell_info_path);
    //fs::create_directories(place_result_path);

    std::ofstream cell_out(cell_info_path.string());
    std::ofstream place_out(place_result_path.string());

    // cell_info out
    cell_out << "name: " << cell.name << std::endl;
    cell_out << "pin: ";
    for (auto pin : cell.IOnets) {
        cell_out << pin << " ";
    }
    cell_out << std::endl << "net: ";
    for (auto net : cell.nets) {
        cell_out << net << " ";
    }
    cell_out << std::endl << "transistor:" << std::endl;

    std::unordered_map<std::string, int> fingers;

    for (int i = 0; i < cellWidth; i++) {
        if (nmos[i].name != "dummy") {
            if (fingers.count(nmos[i].name) == 0) {
                fingers[nmos[i].name] = 1;
            }
            else fingers[nmos[i].name]++;
        }
        if (pmos[i].name != "dummy") {
            if (fingers.count(pmos[i].name) == 0) {
                fingers[pmos[i].name] = 1;
            }
            else fingers[pmos[i].name]++;
        }
    }

    place_out << "mos:" << std::endl;
    std::unordered_map<std::string, int> finger_counter;
    // PMOS placement
    for (int i = 0; i < cellWidth; i++) {
        auto pmos_name = pmos[i].name;
        if (pmos_name != "dummy") {
            assert(fingers.count(pmos_name) > 0);
            if (finger_counter.count(pmos_name) == 0) finger_counter[pmos_name] = 1;
            else finger_counter[pmos_name]++;
            int cur_finger = finger_counter[pmos_name];
            
            if (fingers[pmos_name] > 1) {
                pmos_name = pmos_name + "_f" + std::to_string(cur_finger);
            }

            cell_out << pmos_name << " " << pmos[i].left << " " << pmos[i].gate << " " << pmos[i].right << " pmos_rvt " << pmos[i].nfin << " 1" << std::endl;
        }
        if (pmos_name != "dummy") place_out << pmos_name << " ";
        else place_out << "NULL ";
    }
    place_out << std::endl;

    // NMOS placement
    for (int i = 0; i < cellWidth; i++) {
        auto nmos_name = nmos[i].name;
        if (nmos_name != "dummy") {
            assert(fingers.count(nmos_name) > 0);
            if (finger_counter.count(nmos_name) == 0) finger_counter[nmos_name] = 1;
            else finger_counter[nmos_name]++;
            int cur_finger = finger_counter[nmos_name];

            if (fingers[nmos_name] > 1) {
                nmos_name = nmos_name + "_f" + std::to_string(cur_finger);
            }

            cell_out << nmos_name << " " << nmos[i].left << " " << nmos[i].gate << " " << nmos[i].right << " nmos_rvt " << nmos[i].nfin << " 1" << std::endl;
        }
        if (nmos_name != "dummy") place_out << nmos_name << " ";
        else place_out << "NULL ";
    }
    place_out << std::endl;


    // finalize
    cell_out << "end";

    place_out << "end" << std::endl;
    place_out << "mosType: PMOS NMOS" << std::endl;
    place_out << "cellWidth: " << cellWidth + 2 << std::endl;


    cell_out.close();
    place_out.close();

}

void PlaceGrid::find_contact_list () {
    
    std::vector<Point> contacts;

    // Diffusion
    for (int i = 0; i < cellWidth; i++) {
        // NMOS Region
        if (nmos[i].gate != "dummy") {
            auto net = nmos[i].left;
            if (net != "dummy" && net != "VDD" && net != "VSS") {
                contacts.emplace_back(4, 2 * i);
                if (nmos[i].nfin > 1) contacts.emplace_back(3, 2 * i);

                contact_list[net].push_back(contacts);
                contacts.clear();
            }

        }
        else if (i > 0) {
            auto net = nmos[i - 1].right;
            if (net != "dummy" && net != "VDD" && net != "VSS") {
                contacts.emplace_back(4, 2 * i);
                if (nmos[i - 1].nfin > 1) contacts.emplace_back(3, 2 * i);

                contact_list[net].push_back(contacts);
                contacts.clear();
            }
        }

        // PMOS Region
        if (pmos[i].gate != "dummy") {
            auto net = pmos[i].left;
            if (net != "dummy" && net != "VDD" && net != "VSS") {
                contacts.emplace_back(0, 2 * i);
                if (pmos[i].nfin > 1) contacts.emplace_back(1, 2 * i);

                contact_list[net].push_back(contacts);
                contacts.clear();
            }

        }
        else if (i > 0) {
            auto net = pmos[i - 1].right;
            if (net != "dummy" && net != "VDD" && net != "VSS") {
                contacts.emplace_back(0, 2 * i);
                if (pmos[i - 1].nfin > 1) contacts.emplace_back(1, 2 * i);

                contact_list[net].push_back(contacts);
                contacts.clear();
            }
        }

        if (i == cellWidth - 1) {
            auto net = pmos[i].right;
            if (net != "dummy" && net != "VDD" && net != "VSS") {
                contacts.emplace_back(0, 2 * i + 2);
                if (pmos[i].nfin > 1) contacts.emplace_back(1, 2 * i + 2);

                contact_list[net].push_back(contacts);
                contacts.clear();
            }

            net = nmos[i].right;
            if (net != "dummy" && net != "VDD" && net != "VSS") {
                contacts.emplace_back(4, 2 * i + 2);
                if (nmos[i].nfin > 1) contacts.emplace_back(3, 2 * i + 2);

                contact_list[net].push_back(contacts);
                contacts.clear();
            }
        }
    }
    
    // Gate
    std::string prev_net;
    for (int i = 0; i < cellWidth; i++) {
        if (i == 0) {
            if (pmos[i].gate == nmos[i].gate) {
                contacts.emplace_back(2, 2 * i + 1);
                prev_net = pmos[i].gate;
            }
            else prev_net = "different";
        }
        else {
            if (pmos[i].gate == nmos[i].gate || (pmos[i].gate == "dummy" || nmos[i].gate == "dummy")) {
                auto curr_net = (pmos[i].gate != "dummy") ? pmos[i].gate : nmos[i].gate;
                if (curr_net == prev_net) {
                    contacts.emplace_back(2, 2 * i);
                    contacts.emplace_back(2, 2 * i + 1);
                }
                else {
                    if (contacts.size() > 0) {
                        contact_list[prev_net].push_back(contacts);
                        contacts.clear();
                        contacts.emplace_back(2, 2 * i + 1);
                    }
                }
                prev_net = curr_net;
            }
            else {
                if (contacts.size() > 0) {
                    contact_list[prev_net].push_back(contacts);
                    contacts.clear();
                }
                prev_net = "different";
            }
        }
        if (i == cellWidth - 1) {
            if (contacts.size() > 0) {
                assert(pmos[i].gate == nmos[i].gate || (pmos[i].gate == "dummy" || nmos[i].gate == "dummy"));
                auto curr_net = (pmos[i].gate != "dummy") ? pmos[i].gate : nmos[i].gate;
                contact_list[curr_net].push_back(contacts);
                contacts.clear();
            }
        }
    }
}


void PlaceGrid::cal_density () {

    int num_row = 5;
    int num_col = 2 * cellWidth + 1;

    int hpwl = 0;

    // Initialize density map
    h_net_den.resize(num_row);
    v_net_den.resize(num_row);
    for (int i = 0; i < num_row; i++) {
        h_net_den[i].resize(num_col);
        v_net_den[i].resize(num_col);
        for (int j = 0; j < num_col; j++) {
            h_net_den[i][j] = 0;
            v_net_den[i][j] = 0;
        }
    }

    std::vector<std::vector<double>> cur_h_net_den, cur_v_net_den;
    cur_h_net_den.resize(num_row);
    cur_v_net_den.resize(num_row);
    for (int i = 0; i < num_row; i++) {
        cur_h_net_den[i].resize(num_col);
        cur_v_net_den[i].resize(num_col);
        for (int j = 0; j < num_col; j++) {
            cur_h_net_den[i][j] = 0;
            cur_v_net_den[i][j] = 0;
        }
    }



    for (auto& it : contact_list) {
        // Initialize cur_net_den
        for (int i = 0; i < num_row; i++) {
            for (int j = 0; j < num_col; j++) {
                cur_h_net_den[i][j] = 0;
                cur_v_net_den[i][j] = 0;
            }
        }


        auto net = it.first;
        auto& contacts = it.second;
        
        assert(contacts.size() > 0);

        // Sum contact point occupation
        for (auto& points : contacts) {
            int num_point = static_cast<int>(points.size());
            double prob = static_cast<double>(1) / num_point;

            for (auto& point : points) {
                cur_h_net_den[point.y][point.x] += prob;
                cur_v_net_den[point.y][point.x] += prob;
            }
        }

        if (contacts.size() <= 1) continue;

        // Get bounding box
        Point lt{-1, -1}, rb{-1, -1};

        for (auto& points : contacts) {
            for (auto& point : points) {
                if (lt.x == -1 && lt.y == -1) lt = point;
                else {
                    if (point.x < lt.x) lt.x = point.x;
                    if (point.y < lt.y) lt.y = point.y;
                }
                if (rb.x == -1 && rb.y == -1) rb = point;
                else {
                    if (point.x > rb.x) rb.x = point.x;
                    if (point.y > rb.y) rb.y = point.y;
                }
            }
        }

        // Special cases
        // Connecting gates only -> expand bbox to all hor tracks
        if (rb.y == 2 && lt.y == 2 && contacts.size() > 1) {
            lt.y = 0; rb.y = num_row - 1;
        }

        hpwl += std::abs(rb.y - lt.y) + std::abs(rb.x - lt.x);

        // Sum density
        double h_density = static_cast<double>(1) / (rb.y - lt.y + 1);
        double v_density = static_cast<double>(1) / (rb.x - lt.x + 1);

        assert(lt.y <= rb.y); assert(lt.x <= rb.x);
        for (int x = lt.x; x <= rb.x; x++) {
            for (int y = lt.y; y <= rb.y; y++) {
                cur_h_net_den[y][x] += h_density;
                cur_v_net_den[y][x] += v_density;
            }
        }

        for (int i = 0; i < num_row; i++) {
            for (int j = 0; j < num_col; j++) {
                h_net_den[i][j] += cur_h_net_den[i][j];
                v_net_den[i][j] += cur_v_net_den[i][j];
            }
        }
    }

    nor_hpwl = static_cast<double>(hpwl) / (num_row + num_col);
    max_h_grid = -1;
    max_v_grid = -1;
    for (int i = 0; i < num_row; i++) {
        for (int j = 0; j < num_col; j++) {
            if (h_net_den[i][j] > max_h_grid) max_h_grid = h_net_den[i][j];
            if (v_net_den[i][j] > max_v_grid) max_v_grid = v_net_den[i][j];
        }
    }
    max_v_row = -1;
    max_h_row = -1;
    for (int i = 0; i < num_row; i++) {
        double sum_v_row = 0;
        double sum_h_row = 0;
        for (int j = 0; j < num_col; j++) {
            sum_v_row += v_net_den[i][j];
            sum_h_row += h_net_den[i][j];
        }
        if (sum_v_row > max_v_row) max_v_row = sum_v_row;
        if (sum_h_row > max_h_row) max_h_row = sum_h_row;
    }
    max_h_column = -1;
    max_v_column = -1;
    for (int j = 0; j < num_col; j++) {
        double sum_h_column = 0;
        double sum_v_column = 0;
        for (int i = 0; i < num_row; i++) {
            sum_h_column += h_net_den[i][j];
            sum_v_column += v_net_den[i][j];
        }
        if (sum_h_column > max_h_column) max_h_column = sum_h_column;
        if (sum_v_column > max_v_column) max_v_column = sum_v_column;
    }
}

void PlaceGrid::cal_cost() {
    find_contact_list();
    cal_density();

    int num_row = 5;
    int num_col = 2 * cellWidth + 1;
    cost = 0;

    for (int x = 0; x < num_col; x++) {
        double h_sum = 0, v_sum = 0;
        for (int y = 0; y < num_row; y++) {
            h_sum += h_net_den[y][x];
            v_sum += v_net_den[y][x];
        }
        hor_cong.push_back(h_sum);
        ver_cong.push_back(v_sum);
        
        cost += h_sum + v_sum;
    }
}
