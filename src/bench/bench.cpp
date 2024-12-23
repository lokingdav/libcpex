#include <sodium.h>
#include <chrono>

#include "../libcpex/libcpex.hpp"

using namespace libcpex;

const int numIters = 1000;
string callDetails = "+123456789|+1987654321|1733427398";

auto startTimer() {
    return std::chrono::high_resolution_clock::now();
}

void endTimer(string testname, const std::chrono::high_resolution_clock::time_point& start, const int iters) {
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << std::endl << testname << " | " << iters << " iterations | Total of " << duration.count() << " microseconds" << std::endl;
    std::cout << "Avg.  " << duration.count() / iters << " microseconds" << std::endl;
    std::cout << "=================================================================" << std::endl;
}

void BenchBlinding() {
    auto keypair = OPRF::Keygen();

    auto start = startTimer();
    for (auto i = 0; i < numIters; i++) {
        auto blinded = OPRF::Blind(callDetails);
    }
    endTimer("OPRF::Blind", start, numIters);
}

void BenchEvaluation() {
    auto keypair = OPRF::Keygen();
    auto blinded = OPRF::Blind(callDetails);

    auto start = startTimer();
    for (auto i = 0; i < numIters; i++) {
        auto eval = OPRF::Evaluate(keypair, blinded.x);
    }
    endTimer("OPRF::Evaluate", start, numIters);
}

void BenchUnblinding() {
    auto keypair = OPRF::Keygen();
    auto blinded = OPRF::Blind(callDetails);
    auto eval = OPRF::Evaluate(keypair, blinded.x);

    auto start = startTimer();
    for (auto i = 0; i < numIters; i++) {
        Bytes label = OPRF::Unblind(eval, blinded.r);
    }
    endTimer("OPRF::Unblind", start, numIters);
}

void BenchEncryption() {
    Bytes key = Ciphering::Keygen();
    Bytes plaintext = Utils::RandomBytes(256); // 2KB

    auto start = startTimer();
    for (auto i = 0; i < numIters; i++) {
        Bytes ctx = Ciphering::Encrypt(key, plaintext);
    }
    endTimer("Ciphering::Encrypt", start, numIters);
}

void BenchDecryption() {
    Bytes key = Ciphering::Keygen();
    Bytes plaintext = Utils::RandomBytes(256); // 2KB
    Bytes ctx = Ciphering::Encrypt(key, plaintext);

    auto start = startTimer();
    for (auto i = 0; i < numIters; i++) {
        Bytes msg = Ciphering::Decrypt(key, ctx);
    }
    endTimer("Ciphering::Decrypt", start, numIters);
}

int main(int argc, char* argv[])
{
    // OPRF
    BenchBlinding();
    BenchEvaluation();
    BenchUnblinding();

    // Ciphering
    BenchEncryption();
    BenchDecryption();

    return 0;
}