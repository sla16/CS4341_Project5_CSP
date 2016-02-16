Items (CSP variables)
We have N items denoted by UPPER case letters (e.g. A, B, C, D, ...). Each item has weight associated with it. All items must be assigned to a bag, and only one bag.

Bags (Variables' domains)
We will denoted the M bags by lower case letters (e.g. p, q, r, s, t, ...). Each bag has a capacity, namely how much weight it can hold. The items must be assigned to the bags such that the sum of their weights do not exceed the the maximum capacity, and the bags must be at least 90% full (Rounded down to the nearest int. A bag with a capacity of 100 must hold at least 90 kg, capacity 101 = at least 90, capacity 4 = at least 3, ect).

Contraints
The constraints are of the following sort:

Bag Fit-Limit (Number of items in each bag): 
Any bag must contain at least x items but no more than y items. We assume that x and y are the same for all bags. 
Unary constraints (involving one variable):
Assume that the thieves are picky, and they require certain items to be placed in certain bags. Hence a unary inclusive constraint specifies that a certain item can only be assigned to certain possible bags. For example, item A can only be assigned to bags p, q, r, or s.
On the other hand, they also require that certain items can't be placed in some bags. In this case, a unary exclusive constraint specifies which bags an item must NOT be allocated to. For example: item B can be assigned to neither bag p nor bag q.
Binary constraints (involving two variables):
Equality: We have binary equality constraint to specify that two items must be placed in the same bag.
Inequality: On the other hand, we use binary inequality constraint to specify that two items must NOT be placed in the same bag.
Mutual Inclusive-ity: Two given items must be simultaneously assigned to a given pair of bags, if at least one of those items is in one of those bags. Mutual Inclusivity constraint says that if either item A gets placed into one of bags p or q, then item B must be placed into the other (and similarly if B is allocated first, A must get into the other).
