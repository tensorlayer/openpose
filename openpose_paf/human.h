#pragma once
#include <map>
#include <vector>

struct body_part_t {
    int part_idx;
    float x;
    float y;
    float score;
};

template <int J> struct human_t_ {
    body_part_t body_parts[J];
    float score;

#define DEBUG
#ifdef DEBUG
    void print() const
    {
        for (int i = 0; i < J; ++i) {
            const auto body_part = body_parts[i];
            if (body_parts.part_idx >= 0) {
                printf("BodyPart:%d-(%.2f, %.2f) score=%.2f ", i, body_part.x,
                       body_part.y, body_part.score);
            }
        }
        printf("score=%.2f\n", score);
    }
#endif
};

using human_t = human_t_<19>;

struct ConnectionCandidate {
    int idx1;
    int idx2;
    float score;
    float etc;
};

inline bool operator>(const ConnectionCandidate &a,
                      const ConnectionCandidate &b)
{
    return a.score > b.score;
}

struct Connection {
    int cid1;
    int cid2;
    float score;
    int peak_id1;
    int peak_id2;
};

struct body_part_ret_t {
    int id;  // id of peak in the list of all peaks
    body_part_ret_t() : id(-1) {}
};

template <int J> struct human_ref_t_ {
    int id;
    body_part_ret_t parts[J];
    float score;
    int n_parts;

    human_ref_t_() : id(-1), score(0), n_parts(0) {}

    bool touches(const std::pair<int, int> &p, const Connection &conn) const
    {
        return parts[p.first].id == conn.cid1 ||
               parts[p.second].id == conn.cid2;
    }
};

using human_ref_t = human_ref_t_<18>;
