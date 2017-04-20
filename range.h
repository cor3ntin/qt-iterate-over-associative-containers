#ifndef QT_PAIR_VIEW_H
#define QT_PAIR_VIEW_H

#include <QPair>
#include <utility>
#include <iterator>
#include <type_traits>
#include <meta/meta.hpp>
#include <range/v3/range_traits.hpp>
#include <range/v3/view_adaptor.hpp>
#include <range/v3/view/view.hpp>


namespace details {

using namespace ranges;
using namespace ranges::v3;


template<typename Rng, template <typename, typename> class Container>
struct associative_pair_view : view_adaptor<associative_pair_view<Rng, Container>, Rng>
{
private:
    friend range_access;
    struct adaptor: adaptor_base
    {
        using pair_type = Container<decltype(iterator_t<Rng>().key()), decltype(iterator_t<Rng>().value())>;

        auto read(iterator_t<Rng> const &it) const -> pair_type
        {
            return pair_type { it.key(), it.value() };

        }
        auto iter_move(iterator_t<Rng> const &it) const ->
        decltype(ranges::iter_move(it))
        {
            return ranges::iter_move(it);
        }
    };
    adaptor begin_adaptor() const
    {
        return {};
    }
    adaptor end_adaptor() const
    {
        return{};
    }
public:
    associative_pair_view() = default;
    explicit associative_pair_view(Rng rng)
        : associative_pair_view::view_adaptor{std::move(rng)}
    {}
    CONCEPT_REQUIRES(SizedRange<Rng>())
    range_size_type_t<Rng> size() const
    {
        return ranges::size(this->base());
    }
};

template<template <typename, typename> class Container>
struct associative_pair_fn
{
    template<typename Rng>
    using Concept = meta::and_<
    InputRange<Rng>,
    Readable<range_value_type_t<Rng>>>;

    template<typename Rng>
    associative_pair_view<ranges::v3::view::all_t<Rng>, Container> operator()(Rng && rng) const
    {
        CONCEPT_ASSERT(InputRange<Rng>());
        return associative_pair_view<ranges::v3::view::all_t<Rng>, Container>{ranges::v3::view::all(static_cast<Rng&&>(rng))};
    }
};

}

RANGES_INLINE_VARIABLE(ranges::v3::view::view<details::associative_pair_fn<std::pair>>, to_std_pairs)
RANGES_INLINE_VARIABLE(ranges::v3::view::view<details::associative_pair_fn<QPair>>, to_qt_pairs)



#endif
