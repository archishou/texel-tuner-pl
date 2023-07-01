#include "pl_tapered.h"
#include "pl_base.h"

#include <array>
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace std;
using namespace Toy;

struct Trace {
    int32_t material[6][2]{};
};

constexpr std::array<int32_t, 6> material = { S(100, 100), S(300, 300), S(300, 300), S(500, 500), S(900, 900) };

static Trace trace_evaluate(const Position& position) {
    Trace trace{};

    for (int i = 0; i < 64; i++) {
        auto piece = position.pieces[i];

        if (piece == Pieces::None) {
            continue;
        }

        if (piece < Pieces::BlackPawn) {
            const int materialIndex = static_cast<int>(piece) - static_cast<int>(Pieces::WhitePawn);
            trace.material[materialIndex][0]++;

        }
        else {
            const int materialIndex = static_cast<int>(piece) - static_cast<int>(Pieces::BlackPawn);
            trace.material[materialIndex][1]++;

        }
    }

    return trace;
}

static coefficients_t get_coefficients(const Trace& trace) {
    coefficients_t coefficients;
    get_coefficient_array(coefficients, trace.material, 6);
    return coefficients;
}

parameters_t ToyEvalTapered::get_initial_parameters() {
    parameters_t parameters;
    get_initial_parameter_array(parameters, material, material.size());
    return parameters;
}

EvalResult ToyEvalTapered::get_fen_eval_result(const string& fen) {
    Position position;
    parse_fen(fen, position);
    auto trace = trace_evaluate(position);
    EvalResult result;
    result.coefficients = get_coefficients(trace);
    result.score = 0;
    return result;
}

void ToyEvalTapered::print_parameters(const parameters_t& parameters) {
    int index = 0;
    stringstream ss;
    print_array(ss, parameters, index, "material", 6);
    cout << ss.str() << "\n";
}
