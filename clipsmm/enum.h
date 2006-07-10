/***************************************************************************
 *   clipsmm C++ wrapper for the CLIPS c library                           *
 *   Copyright (C) 2006 by Rick L. Vinyard, Jr.                            *
 *   rvinyard@cs.nmsu.edu                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of version 2 of the GNU General Public License as  *
 *   published by the Free Software Foundation.                            *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA              *
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
