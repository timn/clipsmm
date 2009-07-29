/***************************************************************************
 *   Copyright (C) 2006 by Rick L. Vinyard, Jr.                            *
 *   rvinyard@cs.nmsu.edu                                                  *
 *                                                                         *
 *   This file is part of the clipsmm library.                             *
 *                                                                         *
 *   The clipsmm library is free software; you can redistribute it and/or  *
 *   modify it under the terms of the GNU General Public License           *
 *   version 3 as published by the Free Software Foundation.               *
 *                                                                         *
 *   The clipsmm library is distributed in the hope that it will be        *
 *   useful, but WITHOUT ANY WARRANTY; without even the implied warranty   *
 *   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU   *
 *   General Public License for more details.                              *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this software. If not see <http://www.gnu.org/licenses/>.  *
 ***************************************************************************/
#ifndef CLIPSENUM_H
#define CLIPSENUM_H

namespace CLIPS {

/**
 * \note This typedef is dependent upon the enum values matching the #defines in CLIPS
 */
typedef enum SalienceEvaluation {
  SALIENCE_EVAL_WHEN_DEFINED,
    SALIENCE_EVAL_WHEN_ACTIVATED,
    SALIENCE_EVAL_EVERY_CYCLE,
} SalienceEvaluation;

/**
 * \note This typedef is dependent upon the enum values matching the #defines in CLIPS
 */
typedef enum ConflictResolution {
  CONFLICT_DEPTH_STRATEGY,
    CONFLICT_BREADTH_STRATEGY,
    CONFLICT_LEX_STRATEGY,
    CONFLICT_MEA_STRATEGY,
    CONFLICT_COMPLEXITY_STRATEGY,
    CONFLICT_SIMPLICITY_STRATEGY,
    CONFLICT_RANDOM_STRATEGY,
    CONFLICT_DEFAULT_STRATEGY=CONFLICT_DEPTH_STRATEGY,
} ConflictResolution;

}

#endif
