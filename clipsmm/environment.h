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
#ifndef CLIPSENVIRONMENT_H
#define CLIPSENVIRONMENT_H

#include <string>
#include <map>

#include <sigc++/sigc++.h>

#include <clipsmm/fact.h>

namespace CLIPS {

/**
 * @author Rick L. Vinyard, Jr. <rvinyard@cs.nmsu.edu>
 */
class Environment: public sigc::trackable {
public:
    Environment();

    ~Environment();

    /**
     * Evaluates a series of commands in the specified file
     * @return false if an error occurred, true otherwise
     */
    bool batch_evaluate( const std::string& filename );

    /**
     * Loads a binary image of constructs into the CLIPS data base
     * @return false if an error occurred, true otherwise
     */
    bool binary_load( const std::string& filename );

    /**
     * Saves a binary image of constructs from the CLIPS data base
     * @return false if an error occurred, true on success
     */
    bool binary_save( const std::string& filename );

    /**
     * Allows a construct to be defined
     * @return false if the construct could not be parsed, true on success
     */
    bool build( const std::string& construct );

    /**
     * Clears the environment
     */
    void clear( );

    /**
     * \todo Eval
     */

    /**
     * \todo FunctionCall
     */

    /**
     * Loads a set of constructs into the CLIPS data base
     * @return Zero if the file couldn’t be opened, -1 if the file
     *         was opened but an error occurred while loading, and 1
     *         if the file was opened and no errors occurred while
     *         loading.
     *
     * If syntactic errors are in the constructs, load still will
     * attempt to read the entire file and error notices will be sent
     * to werror.
     */
    int load( const std::string& filename );

    /**
     * Resets the CLIPS environment
     */
    void reset();

    /**
     * Saves a set of constructs to the specified file
     * @return false if an error occurred, true on success
     */
    bool save( const std::string& filename );

    /**
     * Returns the current state of the auto-float dividend behavior.
     * When enabled, the dividend of the division function is automatically converted
     * to a floating point number.
     * @return true if enabled, false if disabled
     */
    bool auto_float_dividend_enabled();

    /**
     * Sets the auto-float dividend behavior.
     * When enabled, the dividend of the division function is automatically converted
     * to a floating point number.
     * Default is enabled.
     * @return the new value for the behavior; true if enabled, false if disabled
     */
    bool use_auto_float_dividend(bool use=true);

    /**
     * Returns the current state of the dynamic constraint checking behavior.
     * When enabled, slot values for newly created data objects are checked for
     * constraint violations.
     * @return true if enabled, false if disabled
     */
    bool dynamic_constraint_checking_enabled();

    /**
     * Sets the dynamic constraint checking behavior.
     * When enabled, slot values for newly created data objects are checked for
     * constraint violations.
     * Default is disabled.
     * @return the new value for the behavior; true if enabled, false if disabled
     */
    bool use_dynamic_constraint_checking(bool use=true);

    /**
     * Returns the current state of the sequence operator recognition behavior.
     * When enabled, multifield variables are expanded and passed as separate arguments
     * in the function call.
     * @return true if enabled, false if disabled
     */
    bool sequence_operator_recognition_enabled();

    /**
     * Sets the sequence operator recognition behavior.
     * When enabled, multifield variables are expanded and passed as separate arguments
     * in the function call.
     * Default is disabled.
     * @return the new value for the behavior; true if enabled, false if disabled
     */
    bool use_sequence_operator_recognition(bool use=true);

    /**
     * Returns the current state of the static constraint checking behavior.
     * When enabled, constraint violations are checked when function calls and constructs
     * are parsed.
     * @return true if enabled, false if disabled
     */
    bool static_constraint_checking_enabled();

    /**
     * Sets the static constraint checking behavior.
     * When enabled, constraint violations are checked when function calls and constructs
     * are parsed.
     * @return the new value for the behavior; true if enabled, false if disabled
     */
    bool use_static_constraint_checking(bool use=true);

    /**
     * Returns the current state of the fact duplication behavior.
     * When disabled, asserting a duplicate of a fact in the fact-list will result in no effect.
     * When enabled, a duplicate fact is asserted with a new fact-index.
     * Default is disabled.
     * @return true if enabled, false if disabled
     */
    bool fact_duplication_enabled();

    /**
     * Sets the static constraint checking behavior.
     * When enabled, constraint violations are checked when function calls and constructs
     * are parsed.
     * @return the new value for the behavior; true if enabled, false if disabled
     */
    bool use_fact_duplication(bool use=true);

    /**
     * Determines if the storing of dribble information is active.
     * @return true if dribbling is active, false if it is inactive
     */
    bool is_dribble_active( );

    /**
     * Turns off the storing of dribble information
     * @return false if an error occurred closing the file; true on success.
     */
    bool dribble_off( );

    /**
     * Allows the dribble function of CLIPS to be turned on
     * @return false if an error occurred opening the file; true on success.
     */
    bool dribble_on( const std::string& dribble_file );

    /**
     * Determine if an item is being watched
     * @param item must be one of the following strings: facts, rules, activations, focus,
     *             compilations, statistics, globals, instances, slots, messages,
     *             message-handlers, generic-functions, method, or deffunctions.
     * @return 1 if the item is watched, 0 if the item is not watched, -1 if the item doesn't exist
     */
    int is_watched( const std::string& item );

    bool watch( const std::string& item );

    bool unwatch( const std::string& item );

    /**
     * Allows rules to execute
     * @return The number of rules that fired
     * @param runlimit How many rules should file
     * If runlimit is negative, rules will fire until the agenda is empty
     */
    long int run( long int runlimit );

    void set_as_current();

    sigc::signal<void> signal_clear();
    sigc::signal<void> signal_periodic();
    sigc::signal<void> signal_reset();

    Fact::pointer assert( const std::string& factstring );

    /** TODO Facts */

    /** Returns a pointer to the underlying CLIPS C object */
    void* cobj();

  protected:
    void* m_cobj;

    sigc::signal<void> m_signal_clear;
    sigc::signal<void> m_signal_periodic;
    sigc::signal<void> m_signal_reset;

    static std::map<void*, Environment*> m_environment_map;
    static void clear_callback(void* env);
    static void periodic_callback(void* env);
    static void reset_callback(void* env);


};

}

#endif
