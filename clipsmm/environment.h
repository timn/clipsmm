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

#include <clipsmm/object.h>
#include <clipsmm/fact.h>
#include <clipsmm/activation.h>
#include <clipsmm/defaultfacts.h>
#include <clipsmm/template.h>
#include <clipsmm/rule.h>
#include <clipsmm/module.h>

namespace CLIPS {

/**
 * @author Rick L. Vinyard, Jr. <rvinyard@cs.nmsu.edu>
 */
class Environment: public Object {
public:
  typedef std::tr1::shared_ptr<Environment> pointer;
  
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
     * Evaluates and expression and returns a vector of the results.
     * If the expression could not be evaluated a zero-length vector
     * is returned.
     */
    Values evaluate( const std::string& expression );

    /**
     * Evaluates a CLIPS function.
     * If the function could not be evaluated a zero-length vector
     * is returned.
     */
    Values function( const std::string& function_name, const std::string& arguments );

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

    bool incremental_reset_enabled();

    bool use_incremental_reset(bool use=true);
    
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

    void set_as_current();

    Fact::pointer assert( const std::string& factstring );

    void clear_focus_stack();
    
    /** TODO Facts */

    DefaultFacts::pointer get_default_facts( const std::string& default_facts_name );

    /** Gets a list of default facts names from all modules */
    std::vector<std::string> get_default_facts_names();

    /** Gets a list of default facts names from a specific module */
    std::vector<std::string> get_default_facts_names(const Module& module);

    /** Gets a list of default facts names from a specific module */
    std::vector<std::string> get_default_facts_names(Module::pointer module);

    DefaultFacts::pointer get_default_facts_list_head();

    Template::pointer get_template( const std::string& template_name );

    /** Gets a list of template names from all modules */
    std::vector<std::string> get_template_names();

    /** Gets a list of template names from a specific module */
    std::vector<std::string> get_template_names(const Module& module);

    /** Gets a list of template names from a specific module */
    std::vector<std::string> get_template_names(Module::pointer module);

    Template::pointer get_template_list_head();

    Rule::pointer get_rule( const std::string& rule_name );

    /** Gets a list of rule names from all modules */
    std::vector<std::string> get_rule_names();

    /** Gets a list of rule names from a specific module */
    std::vector<std::string> get_rule_names(const Module& module);

    /** Gets a list of rule names from a specific module */
    std::vector<std::string> get_rule_names(Module::pointer module);

    Rule::pointer get_rule_list_head();

    void remove_rules();

    Module::pointer get_module( const std::string& module_name );

    Module::pointer get_current_module();

    std::vector<std::string> get_module_names();

    Module::pointer get_module_list_head();

    /**
     * Refreshes the agenda for all modules.
     * Recomputes the salience values for all activations on the agenda
     * and then reorders the agenda.
     */
    void refresh_agenda();

    /**
     * Refreshes the agenda for a specific module.
     * Recomputes the salience values for all activations on the agenda
     * and then reorders the agenda.
     */
    void refresh_agenda(const Module& module);

    /**
     * Refreshes the agenda for a specific module.
     * Recomputes the salience values for all activations on the agenda
     * and then reorders the agenda.
     */
    void refresh_agenda(Module::pointer module);

    /**
     * Reorders the agenda for all modules.
     * Reorders the agenda based on the current conflict resolution
     * strategy and current activation saliences.
     */
    void reorder_agenda();

    /**
     * Reorders the agenda for a specific module.
     * Reorders the agenda based on the current conflict resolution
     * strategy and current activation saliences.
     */
    void reorder_agenda(const Module& module);

    /**
     * Reorders the agenda for a specific module.
     * Reorders the agenda based on the current conflict resolution
     * strategy and current activation saliences.
     */
    void reorder_agenda(Module::pointer module);

    /**
     * Allows rules to execute
     * @return The number of rules that fired
     * @param runlimit How many rules should file
     * If runlimit is negative, rules will fire until the agenda is empty
     */
    long int run( long int runlimit=-1 );

    /** TODO SetSalienceEvaluation */

    /** TODO SetStrategy */

    /** TODO ListDefmodules */

    /**
     * Checks whether the agenda has changed and emits the agenda changed signal if it has.
     * The agenda does not include any callbacks when the agenda is changed.
     * This method returns true if the agenda has changed and emits the
     * agenda changed signal.
     */
    bool check_agenda_changed();
    
    Module::pointer get_focused_module();

    std::vector<std::string> get_focus_stack();

    Activation::pointer get_activation_list_head();

    sigc::signal<void> signal_clear();
    sigc::signal<void> signal_periodic();
    sigc::signal<void> signal_reset();
    sigc::signal<void> signal_rule_firing();
    sigc::signal<void> signal_agenda_changed();

  protected:
    sigc::signal<void> m_signal_clear;
    sigc::signal<void> m_signal_periodic;
    sigc::signal<void> m_signal_reset;
    sigc::signal<void> m_signal_rule_firing;
    sigc::signal<void> m_signal_agenda_changed;

    static std::map<void*, Environment*> m_environment_map;
    
    static void clear_callback(void* env);
    static void periodic_callback(void* env);
    static void reset_callback(void* env);
    static void rule_firing_callback(void* end);

};

}

#endif
