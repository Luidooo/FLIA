(define (domain lightsOut)
  (:types line column - object)
  (:predicates

    (red ?x - column ?y - line)
    (green ?x - column ?y - line)
    (blue ?x - column ?y - line)
    (white ?x - column ?y - line)

    (button ?x ?y - object)

    (normal ?x - column ?y - line)
    (broken1 ?x - column ?y - line)
    (broken2 ?x - column ?y - line)
    (broken3 ?x - column ?y - line)
    (broken4 ?x - column ?y - line))

    (:action click
      :parameters ( ?x - column ?y - line)
      :precondition ( and)
      :effect (and
		(when (and (not (broken1 ?x ?y)) (red ?x ?y)) (and (not (red ?x ?y)) (green ?x ?y)))
		(when (and (not (broken1 ?x ?y)) (green ?x ?y)) (and (not (green ?x ?y)) (blue ?x ?y)))
		(when (and (not (broken1 ?x ?y)) (blue ?x ?y)) (and (not (blue ?x ?y)) (white ?x ?y)))
		(when (and (not (broken1 ?x ?y)) (white ?x ?y)) (and (not (white ?x ?y)) (red ?x ?y)))

		(forall
		  (?w - column)(and
			(when (button ?w ?y) (when (and (not (broken2 ?w ?y)) (red ?w ?y)) (and (not (red ?w ?y)) (green ?w ?y))))
			(when (button ?w ?y) (when (and (not (broken4 ?w ?y)) (red ?w ?y)) (and (not (red ?w ?y)) (green ?w ?y))))

			(when (button ?w ?y) (when (and (not (broken2 ?w ?y)) (green ?w ?y)) (and (not (green ?w ?y)) (blue ?w ?y))))
			(when (button ?w ?y) (when (and (not (broken4 ?w ?y)) (green ?w ?y)) (and (not (green ?w ?y)) (blue ?w ?y))))

			(when (button ?w ?y) (when (and (not (broken2 ?w ?y)) (blue ?w ?y)) (and (not (blue ?w ?y)) (white ?w ?y))))
			(when (button ?w ?y) (when (and (not (broken4 ?w ?y)) (blue ?w ?y)) (and (not (blue ?w ?y)) (white ?w ?y))))

			(when (button ?w ?y) (when (and (not (broken2 ?w ?y)) (white ?w ?y)) (and (not (white ?w ?y)) (red ?w ?y))))
			(when (button ?w ?y) (when (and (not (broken4 ?w ?y)) (white ?w ?y)) (and (not (white ?w ?y)) (red ?w ?y))))))

		(forall
		  (?w - line)(and
			(when (button ?x ?w) (when (and (not (broken3 ?x ?w)) (red ?x ?w)) (and (not (red ?x ?w)) (green ?x ?w))))
			(when (button ?x ?w) (when (and (not (broken4 ?x ?w)) (red ?x ?w)) (and (not (red ?x ?w)) (green ?x ?w))))

			(when (button ?x ?w) (when (and (not (broken3 ?x ?w)) (green ?x ?w)) (and (not (green ?x ?w)) (blue ?x ?w))))
			(when (button ?x ?w) (when (and (not (broken4 ?x ?w)) (green ?x ?w)) (and (not (green ?x ?w)) (blue ?x ?w))))

			(when (button ?x ?w) (when (and (not (broken3 ?x ?w)) (blue ?x ?w)) (and (not (blue ?x ?w)) (white ?x ?w))))
			(when (button ?x ?w) (when (and (not (broken4 ?x ?w)) (blue ?x ?w)) (and (not (blue ?x ?w)) (white ?x ?w))))

			(when (button ?x ?w) (when (and (not (broken3 ?x ?w)) (white ?x ?w)) (and (not (white ?x ?w)) (red ?x ?w))))
			(when (button ?x ?w) (when (and (not (broken4 ?x ?w)) (white ?x ?w)) (and (not (white ?x ?w)) (red ?x ?w)))))))))

