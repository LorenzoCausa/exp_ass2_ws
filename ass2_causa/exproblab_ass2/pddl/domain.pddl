(define (domain my_domain)

	(:requirements :strips :typing :durative-actions :universal-preconditions )

	(:types
		waypoint 
	)

	(:predicates
		(robot_at ?wp - waypoint)
		(hint_taken ?wp - waypoint)
		(hp_checked)
		(hp_tested)
		(not_initialized)
	)

	;; Move to any waypoint
	(:durative-action goto_waypoint
		:parameters (?from ?to - waypoint)
		:duration ( = ?duration 6)
		:condition  (and 
					(at start (robot_at ?from)))
		:effect (and
				(at end (robot_at ?to))
				(at start (not (robot_at ?from))))
	)

	;; Take hint from the marker
	(:durative-action take_hint
		:parameters (?l - waypoint)
		:duration ( = ?duration 3)
		:condition (and(over all (robot_at ?l)) )
		:effect (at end (hint_taken ?l))
	)

	;; check with armor if hp consistent
	(:durative-action check_hp
		:parameters ()
		:duration ( = ?duration 1)
		:condition (over all (forall (?wp - waypoint)(hint_taken ?wp))) 
		:effect (at end (hp_checked))
	)

	;; Test with oracle if hp is correct
	(:durative-action test_hp
		:parameters ()
		:duration ( = ?duration 1)
		:condition (over all(hp_checked)) 
		:effect (at end (hp_tested))
	)

;; Initilize the system
	(:durative-action initialize
		:parameters (?l - waypoint)
		:duration ( = ?duration 10)
		:condition (over all(not_initialized)) 
		:effect (and(at end (not(not_initialized)))(at end (robot_at ?l)))
	)
)
