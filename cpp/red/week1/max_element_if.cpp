template<typename ForwardIterator, typename UnaryPredicate>
ForwardIterator max_element_if(ForwardIterator first,
                               ForwardIterator last,
                               UnaryPredicate pred)
{
    ForwardIterator res = last;
    for (ForwardIterator it = first; it != last; it++) {
        if (pred(*it)) {
            if (res == last || *it > *res) {
                res = it;
            }
        }
    }
    return res;
}