#ifndef EASYIMPORT_H
#define EASYIMPORT_H

#include <memory>

using std::shared_ptr;
using std::make_shared;
using std::weak_ptr;
using std::unique_ptr;
using std::make_unique;

using std::move;
using std::forward;

template <typename R>
constexpr inline R * unique_unwrap(unique_ptr<R> && unq) {
    R * result = unq.get();
    unq.release();
    return result;
}

#endif // EASYIMPORT_H
