#include "voprf.hpp"

namespace libcpex {
    VOPRF_Blinded VOPRF::Blind(const std::string &msg) {
        VOPRF_Blinded blinded;
        blinded.p = Point::HashToPoint(msg);
        blinded.r = PrivateKey::Keygen();
        blinded.x = Point::Mul(blinded.p, blinded.r);
        return blinded;
    }

    Point VOPRF::Unblind(const Point& fx, const PrivateKey& r) {
        return Point::Mul(fx, r.Inverse());
    }

    Point VOPRF::Evaluate(const PrivateKey& sk, const Point& x) {
        return Point::Mul(x, sk);
    }

    bool VOPRF::Verify(const PublicKey& pk, const Point& x, const Point& y) {
        Pairing e1 = Pairing::Pair(x, pk);
        Pairing e2 = Pairing::Pair(y, PublicKey::GetBase());
        return e1 == e2;
    }
} // namespace libcpex