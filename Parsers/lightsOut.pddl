(define (domain lightsOut)
  (:requirements :strips :typing :equality)
  (:types location - object)
  (:predicates
    (red  ?yx - location)
    (green  ?yx - location)
    (blue  ?yx - location)
    (white  ?yx - location)

    (line ?yx ?wz - location)
    (column ?yx ?wz - location)

    (broken1  ?yx - location)
    (broken2  ?yx - location)
    (broken3  ?yx - location)
    (broken4  ?yx - location))

  (:action click
    :parameters( ?yx - location)
    :precondition ( and)
    :effect (and
		      (when (not (broken1 ?yx)) (and
						(when (red ?yx) (and (not (red ?yx)) (green ?yx)))
						(when (green ?yx) (and (not (green ?yx)) (blue ?yx)))
						(when (blue ?yx) (and (not (blue ?yx)) (white ?yx)))
						(when (white ?yx) (and (not (white ?yx)) (red ?yx)))))
					(forall
						(?wz - location) (and 
							(when (and (line ?yx ?wz) (not (= ?yx ?wz)) (not (broken3 ?wz)) (not (broken4 ?wz))) (and
								(when (red ?wz) (and (not (red ?wz)) (green ?wz)))
								(when (green ?wz) (and (not (green ?wz)) (blue ?wz)))
								(when (blue ?wz) (and (not (blue ?wz)) (white ?wz)))
								(when (white ?wz) (and (not (white ?wz)) (red ?wz)))))
							(when (and (column ?yx ?wz) (not (= ?yx ?wz)) (not (broken2 ?wz)) (not (broken4 ?wz))) (and
								(when (red ?wz) (and (not (red ?wz)) (green ?wz)))
								(when (green ?wz) (and (not (green ?wz)) (blue ?wz)))
								(when (blue ?wz) (and (not (blue ?wz)) (white ?wz)))
								(when (white ?wz) (and (not (white ?wz)) (red ?wz)))))))

