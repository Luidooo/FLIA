(define (problem lightsOut1)
  (:domain lightsOut)
  (:objects

    l1 l2 l3
    l4 l5 l6
    l7 l8 l9 - line

    c1 c2 c3
    c4 c5 c6
    c7 c8 c9 - column

    red green blue white - color
  )
  (:init)

    (normal l0 c0)
    (normal l0 c1)
    (normal l0 c2)
    (normal l1 c0)
    (normal l1 c1)
    (normal l1 c2)
    (normal l2 c0)
    (normal l2 c1)
    (normal l2 c2)
    
    (color l0 c0 white)
    (color l0 c1 blue)
    (color l0 c2 white)
    (color l1 c0 blue)
    (color l1 c1 blue)
    (color l1 c2 blue)
    (color l2 c0 white)
    (color l2 c1 blue)
    (color l2 c2 white)

    (next red green)
    (next green blue)
    (next blue white)
    (next white red)

  (:goal
    (color l0 c0 white)
    (color l0 c1 white)
    (color l0 c2 white)
    (color l1 c0 white)
    (color l1 c1 white)
    (color l1 c2 white)
    (color l2 c0 white)
    (color l2 c1 white)
    (color l2 c2 white)))
