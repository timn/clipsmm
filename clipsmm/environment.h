/***************************************************************************
 *   Copyright (C) 2006 by Rick L. Vinyard, Jr.  <rvinyard@cs.nmsu.edu>    *
 *   Copyright (C) 2011-2013 by Tim Niemueller [http://www.niemueller.de]  *
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
#ifndef CLIPSENVIRONMENT_H
#define CLIPSENVIRONMENT_H

#include <string>
#include <map>
#include <stdexcept>
#include <map>
#include <queue>

#include <cstdio>

#include <sigc++/sigc++.h>
#include <glibmm.h>

#include <clipsmm/enum.h>
#include <clipsmm/object.h>

#include <clipsmm/activation.h>
#include <clipsmm/defaultfacts.h>
#include <clipsmm/fact.h>
#include <clipsmm/function.h>
#include <clipsmm/global.h>
#include <clipsmm/module.h>
#include <clipsmm/rule.h>
#include <clipsmm/template.h>

#include <clipsmm/utility.h>
#include <clipsmm/any.h>

extern "C" {
  int EnvDefineFunction2WithContext( void *, char *, int, int ( * ) ( void * ), char *, char *, void * );
}

namespace CLIPS {

  /**
   * @author Rick L. Vinyard, Jr. <rvinyard@cs.nmsu.edu>
   */
  class Environment: public Object {
    public:
      typedef CLIPSPointer<Environment> pointer;

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
      Values function( const std::string& function_name, const std::string& arguments=std::string() );

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
      bool use_auto_float_dividend( bool use = true );

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
      bool use_dynamic_constraint_checking( bool use = true );

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
      bool use_sequence_operator_recognition( bool use = true );

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
      bool use_static_constraint_checking( bool use = true );

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
      bool use_fact_duplication( bool use = true );

      bool incremental_reset_enabled();

      bool use_incremental_reset( bool use = true );

      bool global_reset_enable();

      bool use_global_reset( bool use=true );

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

      Fact::pointer assert_fact( const std::string& factstring );
      Fact::pointer assert_fact( Fact::pointer fact );
      Fact::pointer assert_fact_f( const char *format, ... );

      void clear_focus_stack();

      /** TODO Facts */

      /** Get facts.
       * @return pointer to the first fact in the environment, use Fact::next() to
       * iterate over all facts. Returns an invalid pointer if no facts have been
       * asserted, yet.
       */
      Fact::pointer get_facts();

      DefaultFacts::pointer get_default_facts( const std::string& default_facts_name );

      /** Gets a list of default facts names from all modules */
      std::vector<std::string> get_default_facts_names();

      /** Gets a list of default facts names from a specific module */
      std::vector<std::string> get_default_facts_names( const Module& module );

      /** Gets a list of default facts names from a specific module */
      std::vector<std::string> get_default_facts_names( Module::pointer module );

      DefaultFacts::pointer get_default_facts_list_head();

      Template::pointer get_template( const std::string& template_name );

      /** Gets a list of template names from all modules */
      std::vector<std::string> get_template_names();

      /** Gets a list of template names from a specific module */
      std::vector<std::string> get_template_names( const Module& module );

      /** Gets a list of template names from a specific module */
      std::vector<std::string> get_template_names( Module::pointer module );

      Template::pointer get_template_list_head();

      Rule::pointer get_rule( const std::string& rule_name );

      /** Gets a list of rule names from all modules */
      std::vector<std::string> get_rule_names();

      /** Gets a list of rule names from a specific module */
      std::vector<std::string> get_rule_names( const Module& module );

      /** Gets a list of rule names from a specific module */
      std::vector<std::string> get_rule_names( Module::pointer module );

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
      void refresh_agenda( const Module& module );

      /**
       * Refreshes the agenda for a specific module.
       * Recomputes the salience values for all activations on the agenda
       * and then reorders the agenda.
       */
      void refresh_agenda( Module::pointer module );

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
      void reorder_agenda( const Module& module );

      /**
       * Reorders the agenda for a specific module.
       * Reorders the agenda based on the current conflict resolution
       * strategy and current activation saliences.
       */
      void reorder_agenda( Module::pointer module );

      /**
       * Allows rules to execute
       * @return The number of rules that fired
       * @param runlimit How many rules should fire
       * If runlimit is negative, rules will fire until the agenda is empty.
       *
       * If a threaded execution is active, this call will block until the
       * threaded execution queue is empty.
       */
      long int run( long int runlimit = -1 );

      /**
       * Executes rules in a separate thread.
       *
       * If an execution thread is already running, the job will be added to
       * the run queue at the priority level specified. The higher the
       * priority, the higher in the queue. After each execution, the run
       * queue is checked and the next highest priority job is executed.
       *
       * If the normal run() method is executing, the execution thread will be
       * created, but will block until the previously executing call to run()
       * is completed. After run() completes, the execution thread will unblock
       * and start execution.
       *
       * \TODO The methods of environment are \b not threadsafe yet. This
       * is just an early look at threading, but making it threadsafe will
       * not be too difficult. For now, to be safe, join the run thread before
       * changing anything in the environment.
       */
      void run_threaded( long int runlimit = -1, int priority = 0 );

      /** Waits until the execution thread is finished */
      void join_run_thread();

      /** Signal emitted when the rules are executed. The signal emits the number of rules executed. */
      sigc::signal<void, long int> signal_run();

      /** Gets the salience evaluation mode */
      SalienceEvaluation get_salience_evaluation();

      /**
       * Sets the salience evaluation mode.
       * @return the old salience evaluation mode
       */
      SalienceEvaluation set_salience_evaluation( SalienceEvaluation se );

      /** Gets the current conflict resolution strategy */
      ConflictResolution get_conflict_resolution_strategy();

      /**
       * Sets the conflict resolution strategy.
       * @return the old conflict resolution strategy
       */
      ConflictResolution set_conflict_resolution_strategy( ConflictResolution cr );

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

      Global::pointer get_global( const std::string& global_name );

      Global::pointer get_global_list_head();

      /** Gets a list of global names from all modules */
      std::vector<std::string> get_globals_names();

      /** Gets a list of global names from a specific module */
      std::vector<std::string> get_globals_names( const Module& module );

      /** Gets a list of global names from a specific module */
      std::vector<std::string> get_globals_names( Module::pointer module );

      bool check_globals_changed();

      Function::pointer get_function( const std::string& function_name );

      Function::pointer get_function_list_head();

      /** Gets a list of function names from all modules */
      std::vector<std::string> get_function_names();

      /** Gets a list of function names from a specific module */
      std::vector<std::string> get_function_names( const Module& module );

      /** Gets a list of function names from a specific module */
      std::vector<std::string> get_function_names( Module::pointer module );

      sigc::signal<void> signal_clear();
      sigc::signal<void> signal_periodic();
      sigc::signal<void> signal_reset();
      sigc::signal<void> signal_rule_firing();
      sigc::signal<void> signal_agenda_changed();
      sigc::signal<void> signal_globals_changed();

      template < typename T_return >
      bool add_function( std::string name, const sigc::slot0<T_return>& slot);

      template < typename T_return, typename T_arg1 >
      bool add_function( std::string name, const sigc::slot1<T_return, T_arg1>& slot);

      template < typename T_return, typename T_arg1, typename T_arg2 >
      bool add_function( std::string name, const sigc::slot2<T_return, T_arg1, T_arg2>& slot);

      template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3 >
      bool add_function( std::string name, const sigc::slot3<T_return, T_arg1, T_arg2, T_arg3>& slot);

      template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
      bool add_function( std::string name, const sigc::slot4<T_return, T_arg1, T_arg2, T_arg3, T_arg4>& slot);

      template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
      bool add_function( std::string name, const sigc::slot5<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>& slot);

      template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
      bool add_function( std::string name, const sigc::slot6<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>& slot);

      template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7 >
      bool add_function( std::string name, const sigc::slot7<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>& slot);

      bool remove_function( std::string name );

    protected:
      /**
       * Holds any dynamically created slots.
       * Type any is used to hold different smart pointers, each of which hold different
       * slots. When a slot is undefined, or at destruction when the map goes out of scope,
       * the memory is reclaimed through the smart pointer.
       */
      std::map<std::string,any> m_slots;

      sigc::signal<void> m_signal_clear;
      sigc::signal<void> m_signal_periodic;
      sigc::signal<void> m_signal_reset;
      sigc::signal<void> m_signal_rule_firing;
      sigc::signal<void> m_signal_agenda_changed;
      sigc::signal<void> m_signal_globals_changed;

      /** Encapsulates the concept of a CLIPS job. Has a priority for comparison and a runlimit */
      typedef struct Job {
        /** Constructor that takes a priority and a CLIPS runlimit */
        Job( int p, long int rl ) : priority(p), runlimit(rl) { }

        /** Comparison operator that compares the priority member */
        bool operator<( const Job& other ) const { return priority < other.priority; }

        /** The priority of this job. The higher the priority, the higher in the queue. */
        int priority;

        /**
         * How many rules should fire.
         * If runlimit is negative, rules will fire until the agenda is empty
         */
        long int runlimit;
      } Job;

      Glib::Thread* m_run_thread; /**< A pointer to the currently running thread */
      std::priority_queue<Job> m_run_queue; /**< A priority queue of jobs to run */
      Glib::Mutex m_mutex_run_queue; /**< Mutex that protects access to the run queue */
      Glib::Mutex m_mutex_run; /**< Mutex that protects against multiple executions */
      Glib::Mutex m_mutex_threaded_run; /**< Mutex that locks when a threaded run is executing */
      Glib::Mutex m_mutex_run_signal; /**< Mutex that protects against multiple signal emits */
      sigc::signal<void, long int> m_signal_run; /**< Signal emitted when a job is run */

      /** Map from function name to restrictions.

       * This is required for some versions of GCC (at least on
       * 4.4.3), where the argstring in add_function() would point to
       * the very same memory on consecutive calls for the same
       * overloaded version, which would lead to the signature of a
       * function in CLIPS being wrong if functions with the same
       * number of arguments but different types would be added.
       */
      std::map<std::string, char *> m_func_restr;

      /** Protected method that does the actual work */
      void threaded_run();

      static std::map<void*, Environment*> m_environment_map;


      static void clear_callback( void* env );
      static void periodic_callback( void* env );
      static void reset_callback( void* env );
      static void rule_firing_callback( void* end );

      static void* strcallback( void* theEnv );

      template < typename T_arg1 >
      static void* strcallback( void* theEnv );

      template < typename T_arg1, typename T_arg2 >
      static void* strcallback( void* theEnv );

      template < typename T_arg1, typename T_arg2, typename T_arg3 >
      static void* strcallback( void* theEnv );

      template < typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
      static void* strcallback( void* theEnv );

      template < typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
      static void* strcallback( void* theEnv );

      template < typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
      static void* strcallback( void* theEnv );

      template < typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7 >
      static void* strcallback( void* theEnv );

      template < typename T_return >
      static T_return callback( void* theEnv );

      template < typename T_return, typename T_arg1 >
      static T_return callback( void* theEnv );

      template < typename T_return, typename T_arg1, typename T_arg2 >
      static T_return callback( void* theEnv );

      template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3 >
      static T_return callback( void* theEnv );

      template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
      static T_return callback( void* theEnv );

      template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
      static T_return callback( void* theEnv );

      template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
      static T_return callback( void* theEnv );

      template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7 >
      static T_return callback( void* theEnv );

      static void callback_multifield( void* theEnv, void *rv);

      template <typename T_arg1>
      static void callback_multifield( void* theEnv, void *rv );

      template <typename T_arg1, typename T_arg2>
      static void callback_multifield( void* theEnv, void *rv );

      template <typename T_arg1, typename T_arg2, typename T_arg3>
      static void callback_multifield( void* theEnv, void *rv );

      template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
      static void callback_multifield( void* theEnv, void *rv );

      template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4,
        typename T_arg5>
      static void callback_multifield( void* theEnv, void *rv );

      template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4,
        typename T_arg5, typename T_arg6>
      static void callback_multifield( void* theEnv, void *rv );

      template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4,
        typename T_arg5, typename T_arg6, typename T_arg7>
      static void callback_multifield( void* theEnv, void *rv );


      static void callback_unknown( void* theEnv, void *rv);

      template <typename T_arg1>
      static void callback_unknown( void* theEnv, void *rv );

      template <typename T_arg1, typename T_arg2>
      static void callback_unknown( void* theEnv, void *rv );

      template <typename T_arg1, typename T_arg2, typename T_arg3>
      static void callback_unknown( void* theEnv, void *rv );

      template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
      static void callback_unknown( void* theEnv, void *rv );

      template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4,
        typename T_arg5>
      static void callback_unknown( void* theEnv, void *rv );

      template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4,
        typename T_arg5, typename T_arg6>
      static void callback_unknown( void* theEnv, void *rv );

      template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4,
        typename T_arg5, typename T_arg6, typename T_arg7>
      static void callback_unknown( void* theEnv, void *rv );

      int ( *get_callback( const sigc::slot0<std::string>& slot ))( void* )
        { return ( int ( * ) ( void* ) ) ( void* ( * ) ( void* ) ) strcallback; }

      template < typename T_arg1 >
      int ( *get_callback( const sigc::slot1<std::string,T_arg1>& slot ))( void* )
        { return ( int ( * ) ( void* ) ) ( void* ( * ) ( void* ) ) strcallback<T_arg1>; }

      template < typename T_arg1, typename T_arg2 >
      int ( *get_callback( const sigc::slot2<std::string,T_arg1,T_arg2>& slot ))( void* )
        { return ( int ( * ) ( void* ) ) ( void* ( * ) ( void* ) ) strcallback<T_arg1,T_arg2>; }

      template < typename T_arg1, typename T_arg2, typename T_arg3 >
      int ( *get_callback( const sigc::slot3<std::string,T_arg1,T_arg2,T_arg3>& slot ))( void* )
        { return (int(*)(void*)) (void* (*)(void*)) strcallback<T_arg1,T_arg2,T_arg3>; }

      template < typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
      int ( *get_callback( const sigc::slot4<std::string,T_arg1,T_arg2,T_arg3,T_arg4>& slot ))( void* )
        { return (int(*)(void*)) (void* (*)(void*)) strcallback<T_arg1,T_arg2,T_arg3,T_arg4>; }

      template < typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
      int ( *get_callback( const sigc::slot5<std::string,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5>& slot ))( void* )
        { return (int(*)(void*)) (void* (*)(void*)) strcallback<T_arg1,T_arg2,T_arg3,T_arg4,T_arg5>; }

      template < typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
      int ( *get_callback( const sigc::slot6<std::string,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6>& slot ))( void* )
        { return (int(*)(void*)) (void* (*)(void*)) strcallback<T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6>; }

      template < typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7 >
      int ( *get_callback( const sigc::slot7<std::string,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6,T_arg7>& slot ))( void* )
        { return (int(*)(void*)) (void* (*)(void*)) strcallback<T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6,T_arg7>; }

      int ( *get_callback( const sigc::slot0<Values>& slot ))( void* )
      { return  (int (*) (void*)) (void (*) (void*, void*)) callback_multifield; }

      template <typename T_arg1>
      int ( *get_callback( const sigc::slot1<Values,T_arg1>& slot ))( void* )
      { return (int (*) (void*)) ( void ( * ) ( void*, void* ) ) callback_multifield<T_arg1>; }

      template <typename T_arg1, typename T_arg2>
      int ( *get_callback( const sigc::slot2<Values,T_arg1,T_arg2>& slot ))( void* )
      { return (int (*) (void*)) ( void ( * ) ( void*, void* ) ) callback_multifield<T_arg1,T_arg2>; }

      template <typename T_arg1, typename T_arg2, typename T_arg3>
        int ( *get_callback( const sigc::slot3<Values,T_arg1,T_arg2,T_arg3>& slot ))( void* )
      { return (int (*) (void*)) ( void ( * ) ( void*, void* ) ) callback_multifield<T_arg1,T_arg2,T_arg3>; }

      template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
        int ( *get_callback( const sigc::slot4<Values,T_arg1,T_arg2,T_arg3,T_arg4>& slot ))( void* )
      { return (int (*) (void*)) ( void ( * ) ( void*, void* ) ) callback_multifield<T_arg1,T_arg2,T_arg3,T_arg4>; }

      template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
        int ( *get_callback( const sigc::slot5<Values,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5>& slot ))( void* )
      { return (int (*) (void*)) ( void ( * ) ( void*, void* ) ) callback_multifield<T_arg1,T_arg2,T_arg3,T_arg4,T_arg5>; }

      template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
        int ( *get_callback( const sigc::slot6<Values,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6>& slot ))( void* )
      { return (int (*) (void*)) ( void ( * ) ( void*, void* ) ) callback_multifield<T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6>; }

      template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
        int ( *get_callback( const sigc::slot7<Values,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6,T_arg7>& slot ))( void* )
      { return (int (*) (void*)) ( void ( * ) ( void*, void* ) ) callback_multifield<T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6,T_arg7>; }


      int ( *get_callback( const sigc::slot0<Value>& slot ))( void* )
      { return  (int (*) (void*)) (void (*) (void*, void*)) callback_unknown; }

      template <typename T_arg1>
      int ( *get_callback( const sigc::slot1<Value,T_arg1>& slot ))( void* )
      { return (int (*) (void*)) ( void ( * ) ( void*, void* ) ) callback_unknown<T_arg1>; }

      template <typename T_arg1, typename T_arg2>
      int ( *get_callback( const sigc::slot2<Value,T_arg1,T_arg2>& slot ))( void* )
      { return (int (*) (void*)) ( void ( * ) ( void*, void* ) ) callback_unknown<T_arg1,T_arg2>; }

      template <typename T_arg1, typename T_arg2, typename T_arg3>
        int ( *get_callback( const sigc::slot3<Value,T_arg1,T_arg2,T_arg3>& slot ))( void* )
      { return (int (*) (void*)) ( void ( * ) ( void*, void* ) ) callback_unknown<T_arg1,T_arg2,T_arg3>; }

      template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
        int ( *get_callback( const sigc::slot4<Value,T_arg1,T_arg2,T_arg3,T_arg4>& slot ))( void* )
      { return (int (*) (void*)) ( void ( * ) ( void*, void* ) ) callback_unknown<T_arg1,T_arg2,T_arg3,T_arg4>; }

      template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
        int ( *get_callback( const sigc::slot5<Value,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5>& slot ))( void* )
      { return (int (*) (void*)) ( void ( * ) ( void*, void* ) ) callback_unknown<T_arg1,T_arg2,T_arg3,T_arg4,T_arg5>; }

      template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
        int ( *get_callback( const sigc::slot6<Value,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6>& slot ))( void* )
      { return (int (*) (void*)) ( void ( * ) ( void*, void* ) ) callback_unknown<T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6>; }

      template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
        int ( *get_callback( const sigc::slot7<Value,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6,T_arg7>& slot ))( void* )
      { return (int (*) (void*)) ( void ( * ) ( void*, void* ) ) callback_unknown<T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6,T_arg7>; }


      template < typename T_return >
      int ( *get_callback( const sigc::slot0<T_return>& slot ))( void* )
        { return (int (*) (void*)) ( T_return ( * ) ( void* ) ) callback<T_return>; }

      template < typename T_return, typename T_arg1 >
      int ( *get_callback( const sigc::slot1<T_return,T_arg1>& slot ))( void* )
        { return ( int ( * ) ( void* ) ) ( T_return ( * ) ( void* ) ) callback<T_return,T_arg1>; }

      template < typename T_return, typename T_arg1, typename T_arg2 >
      int ( *get_callback( const sigc::slot2<T_return,T_arg1,T_arg2>& slot ))( void* )
        { return ( int ( * ) ( void* ) ) ( T_return ( * ) ( void* ) ) callback<T_return,T_arg1,T_arg2>; }

      template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3 >
      int ( *get_callback( const sigc::slot3<T_return,T_arg1,T_arg2,T_arg3>& slot ))( void* )
        { return (int(*)(void*)) (T_return(*)(void*)) callback<T_return,T_arg1,T_arg2,T_arg3>; }

      template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
      int ( *get_callback( const sigc::slot4<T_return,T_arg1,T_arg2,T_arg3,T_arg4>& slot ))( void* )
        { return (int(*)(void*)) (T_return(*)(void*)) callback<T_return,T_arg1,T_arg2,T_arg3,T_arg4>; }

      template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
      int ( *get_callback( const sigc::slot5<T_return,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5>& slot ))( void* )
        { return (int(*)(void*)) (T_return(*)(void*)) callback<T_return,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5>; }

      template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
      int ( *get_callback( const sigc::slot6<T_return,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6>& slot ))( void* )
        { return (int(*)(void*)) (T_return(*)(void*)) callback<T_return,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6>; }

      template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7 >
      int ( *get_callback( const sigc::slot7<T_return,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6,T_arg7>& slot ))( void* )
        { return (int(*)(void*)) (T_return(*)(void*)) callback<T_return,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6,T_arg7>; }

      char * get_function_restriction(std::string &name);

      template <typename T_arg1>
        char * get_function_restriction(std::string &name);

      template <typename T_arg1, typename T_arg2>
        char * get_function_restriction(std::string &name);

      template <typename T_arg1, typename T_arg2, typename T_arg3>
        char * get_function_restriction(std::string &name);

      template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
        char * get_function_restriction(std::string &name);

      template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
        char * get_function_restriction(std::string &name);

      template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
        char * get_function_restriction(std::string &name);

      template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
        char * get_function_restriction(std::string &name);


      static int get_arg_count( void* env );
      static void* get_function_context( void* env );
      static void  set_return_values( void *env, void *rv, const Values &v);
      static void  set_return_value( void *env, void *rv, const Value &v);
      static void* add_symbol( const char* s );


  };


  inline char *
  Environment::get_function_restriction(std::string &name) {
    if (m_func_restr.find(name) != m_func_restr.end())  free(m_func_restr[name]);
    char *restr = (char *)malloc(4); m_func_restr[name] = restr;
    snprintf(restr, 4, "00u");
    return restr;
  }

  template <typename T_arg1>
  inline char *
  Environment::get_function_restriction(std::string &name) {
    if (m_func_restr.find(name) != m_func_restr.end())  free(m_func_restr[name]);
    char *restr = (char *)malloc(5); m_func_restr[name] = restr;
    snprintf(restr, 5, "11u%c", get_argument_code<T_arg1>());
    return restr;
  }

  template <typename T_arg1, typename T_arg2>
  inline char *
  Environment::get_function_restriction(std::string &name) {
    if (m_func_restr.find(name) != m_func_restr.end())  free(m_func_restr[name]);
    char *restr = (char *)malloc(6); m_func_restr[name] = restr;
    snprintf(restr, 6, "22u%c%c", get_argument_code<T_arg1>(), get_argument_code<T_arg2>());
    return restr;
  }

  template <typename T_arg1, typename T_arg2, typename T_arg3>
  inline char *
  Environment::get_function_restriction(std::string &name) {
    if (m_func_restr.find(name) != m_func_restr.end())  free(m_func_restr[name]);
    char *restr = (char *)malloc(7); m_func_restr[name] = restr;
    snprintf(restr, 7, "33u%c%c%c", get_argument_code<T_arg1>(), get_argument_code<T_arg2>(),
             get_argument_code<T_arg3>());
    return restr;
  }

  template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
  inline char *
  Environment::get_function_restriction(std::string &name) {
    if (m_func_restr.find(name) != m_func_restr.end())  free(m_func_restr[name]);
    char *restr = (char *)malloc(8); m_func_restr[name] = restr;
    snprintf(restr, 8, "44u%c%c%c%c", get_argument_code<T_arg1>(), get_argument_code<T_arg2>(),
             get_argument_code<T_arg3>(), get_argument_code<T_arg4>());
    return restr;
  }

  template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4,
    typename T_arg5>
  inline char *
  Environment::get_function_restriction(std::string &name) {
    if (m_func_restr.find(name) != m_func_restr.end())  free(m_func_restr[name]);
    char *restr = (char *)malloc(9); m_func_restr[name] = restr;
    snprintf(restr, 9, "55u%c%c%c%c%c", get_argument_code<T_arg1>(), get_argument_code<T_arg2>(),
             get_argument_code<T_arg3>(), get_argument_code<T_arg4>(), get_argument_code<T_arg5>());
    return restr;
  }

  template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4,
    typename T_arg5, typename T_arg6>
  inline char *
  Environment::get_function_restriction(std::string &name) {
    if (m_func_restr.find(name) != m_func_restr.end())  free(m_func_restr[name]);
    char *restr = (char *)malloc(10); m_func_restr[name] = restr;
    snprintf(restr, 10, "66u%c%c%c%c%c%c", get_argument_code<T_arg1>(), get_argument_code<T_arg2>(),
             get_argument_code<T_arg3>(), get_argument_code<T_arg4>(), get_argument_code<T_arg5>(),
             get_argument_code<T_arg6>());
    return restr;
  }

  template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4,
    typename T_arg5, typename T_arg6, typename T_arg7>
  inline char *
  Environment::get_function_restriction(std::string &name) {
    if (m_func_restr.find(name) != m_func_restr.end())  free(m_func_restr[name]);
    char *restr = (char *)malloc(11); m_func_restr[name] = restr;
    snprintf(restr, 11, "77u%c%c%c%c%c%c%c", get_argument_code<T_arg1>(), get_argument_code<T_arg2>(),
             get_argument_code<T_arg3>(), get_argument_code<T_arg4>(), get_argument_code<T_arg5>(),
             get_argument_code<T_arg6>(), get_argument_code<T_arg7>());
    return restr;
  }


  template < typename T_return>
  inline
  T_return Environment::callback( void* theEnv ) {
    sigc::slot0<T_return>* cb;
    void * cbptr = get_function_context( theEnv );
    if ( cbptr ) {
      if ( get_arg_count( theEnv ) != 0 )
        throw std::logic_error( "clipsmm: wrong # args on slot callback; expected 0" );
      cb = static_cast<sigc::slot0<T_return>*>( cbptr );
      return ( *cb ) ();
    }
    throw;
  }

  template < typename T_return, typename T_arg1 >
  inline
  T_return Environment::callback( void* theEnv ) {
    sigc::slot1<T_return,T_arg1>* cb;
    void * cbptr = get_function_context( theEnv );
    T_arg1 arg1;
    if ( cbptr ) {
      if ( get_arg_count( theEnv ) != 1 )
        throw std::logic_error( "clipsmm: wrong # args on slot callback; expected 1" );
      get_argument( theEnv, 1, arg1 );
      cb = static_cast<sigc::slot1<T_return,T_arg1>*>( cbptr );
      return ( *cb ) ( arg1 );
    }
    throw;
  }

  template < typename T_return, typename T_arg1, typename T_arg2 >
  inline
  T_return Environment::callback( void* theEnv ) {
    sigc::slot2<T_return, T_arg1, T_arg2>* cb;
    void * cbptr = get_function_context( theEnv );
    T_arg1 arg1;
    T_arg2 arg2;
    if ( cbptr ) {
      if ( get_arg_count( theEnv ) != 2 )
        throw std::logic_error( "clipsmm: wrong # args on slot callback; expected 2" );
      get_argument( theEnv, 1, arg1 );
      get_argument( theEnv, 2, arg2 );
      cb = static_cast<sigc::slot2<T_return, T_arg1, T_arg2>*>( cbptr );
      return ( *cb ) ( arg1, arg2 );
    }
    throw;
  }

  template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3 >
  inline
  T_return Environment::callback( void* theEnv ) {
    sigc::slot3<T_return,T_arg1,T_arg2,T_arg3>* cb;
    void * cbptr = get_function_context( theEnv );
    T_arg1 arg1;
    T_arg2 arg2;
    T_arg3 arg3;
    if ( cbptr ) {
      if ( get_arg_count( theEnv ) != 3 )
        throw std::logic_error( "clipsmm: wrong # args on slot callback; expected 3" );
      get_argument( theEnv, 1, arg1 );
      get_argument( theEnv, 2, arg2 );
      get_argument( theEnv, 3, arg3 );
      cb = static_cast<sigc::slot3<T_return, T_arg1, T_arg2,T_arg3>*>( cbptr );
      return ( *cb ) ( arg1, arg2, arg3 );
    }
    throw;
  }

  template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
  inline
  T_return Environment::callback( void* theEnv ) {
    sigc::slot4<T_return,T_arg1,T_arg2,T_arg3,T_arg4>* cb;
    void * cbptr = get_function_context( theEnv );
    T_arg1 arg1;
    T_arg2 arg2;
    T_arg3 arg3;
    T_arg4 arg4;
    if ( cbptr ) {
      if ( get_arg_count( theEnv ) != 4 )
        throw std::logic_error( "clipsmm: wrong # args on slot callback; expected 4" );
      get_argument( theEnv, 1, arg1 );
      get_argument( theEnv, 2, arg2 );
      get_argument( theEnv, 3, arg3 );
      get_argument( theEnv, 4, arg4 );
      cb = static_cast<sigc::slot4<T_return, T_arg1, T_arg2,T_arg3,T_arg4>*>( cbptr );
      return ( *cb ) ( arg1, arg2, arg3, arg4 );
    }
    throw;
  }

  template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
  inline
  T_return Environment::callback( void* theEnv ) {
    sigc::slot5<T_return,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5>* cb;
    void * cbptr = get_function_context( theEnv );
    T_arg1 arg1;
    T_arg2 arg2;
    T_arg3 arg3;
    T_arg4 arg4;
    T_arg5 arg5;
    if ( cbptr ) {
      if ( get_arg_count( theEnv ) != 5 )
        throw std::logic_error( "clipsmm: wrong # args on slot callback; expected 5" );
      get_argument( theEnv, 1, arg1 );
      get_argument( theEnv, 2, arg2 );
      get_argument( theEnv, 3, arg3 );
      get_argument( theEnv, 4, arg4 );
      get_argument( theEnv, 5, arg5 );
      cb = static_cast<sigc::slot5<T_return, T_arg1, T_arg2,T_arg3,T_arg4,T_arg5>*>( cbptr );
      return ( *cb ) ( arg1, arg2, arg3, arg4, arg5 );
    }
    throw;
  }

 template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
 inline
 T_return Environment::callback( void* theEnv ) {
   sigc::slot6<T_return,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6>* cb;
   void * cbptr = get_function_context( theEnv );
   T_arg1 arg1;
   T_arg2 arg2;
   T_arg3 arg3;
   T_arg4 arg4;
   T_arg5 arg5;
   T_arg6 arg6;
   if ( cbptr ) {
     if ( get_arg_count( theEnv ) != 6 )
       throw std::logic_error( "clipsmm: wrong # args on slot callback; expected 6" );
     get_argument( theEnv, 1, arg1 );
     get_argument( theEnv, 2, arg2 );
     get_argument( theEnv, 3, arg3 );
     get_argument( theEnv, 4, arg4 );
     get_argument( theEnv, 5, arg5 );
     get_argument( theEnv, 6, arg6 );
     cb = static_cast<sigc::slot6<T_return, T_arg1, T_arg2,T_arg3,T_arg4,T_arg5,T_arg6>*>( cbptr );
     return ( *cb ) ( arg1, arg2, arg3, arg4, arg5, arg6 );
   }
   throw;
 }

  template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7 >
  inline
  T_return Environment::callback( void* theEnv ) {
    sigc::slot7<T_return,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6,T_arg7>* cb;
    void * cbptr = get_function_context( theEnv );
    T_arg1 arg1;
    T_arg2 arg2;
    T_arg3 arg3;
    T_arg4 arg4;
    T_arg5 arg5;
    T_arg6 arg6;
    T_arg7 arg7;
    if ( cbptr ) {
      if ( get_arg_count( theEnv ) != 7 )
        throw std::logic_error( "clipsmm: wrong # args on slot callback; expected 7" );
      get_argument( theEnv, 1, arg1 );
      get_argument( theEnv, 2, arg2 );
      get_argument( theEnv, 3, arg3 );
      get_argument( theEnv, 4, arg4 );
      get_argument( theEnv, 5, arg5 );
      get_argument( theEnv, 6, arg6 );
      get_argument( theEnv, 7, arg7 );
      cb = static_cast<sigc::slot7<T_return, T_arg1, T_arg2,T_arg3,T_arg4,T_arg5,T_arg6,T_arg7>*>( cbptr );
      return ( *cb ) ( arg1, arg2, arg3, arg4, arg5, arg6, arg7 );
    }
    throw;
  }

  inline
  void Environment::callback_multifield( void* theEnv, void *rv) {
    sigc::slot0<Values>* cb;
    void * cbptr = get_function_context( theEnv );
    if ( cbptr ) {
      if ( get_arg_count( theEnv ) != 0 )
        throw std::logic_error( "clipsmm/mf: wrong # args on slot callback; expected 0" );
      cb = static_cast<sigc::slot0<Values>*>( cbptr );
      Values v = ( *cb ) ();
      set_return_values(theEnv, rv, v);
      return;
    }
    throw;
  }

  template <typename T_arg1>
  inline
  void Environment::callback_multifield( void* theEnv, void *rv) {
    sigc::slot1<Values, T_arg1>* cb;
    void * cbptr = get_function_context( theEnv );
    T_arg1 arg1;
    if ( cbptr ) {
      if ( get_arg_count( theEnv ) != 1 )
        throw std::logic_error( "clipsmm/mf: wrong # args on slot callback; expected 1" );
      cb = static_cast<sigc::slot1<Values, T_arg1>*>( cbptr );
      get_argument(theEnv, 1, arg1);
      Values v = ( *cb ) (arg1);
      set_return_values(theEnv, rv, v);
      return;
    }
    throw;
  }

  template <typename T_arg1, typename T_arg2>
  inline
  void Environment::callback_multifield( void* theEnv, void *rv) {
    sigc::slot2<Values, T_arg1, T_arg2>* cb;
    void * cbptr = get_function_context( theEnv );
    T_arg1 arg1;
    T_arg2 arg2;
    if ( cbptr ) {
      if ( get_arg_count( theEnv ) != 2 )
        throw std::logic_error( "clipsmm/mf: wrong # args on slot callback; expected 2" );
      cb = static_cast<sigc::slot2<Values, T_arg1, T_arg2>*>( cbptr );
      get_argument(theEnv, 1, arg1);
      get_argument(theEnv, 2, arg2);
      Values v = ( *cb ) (arg1, arg2);
      set_return_values(theEnv, rv, v);
      return;
    }
    throw;
  }


  template <typename T_arg1, typename T_arg2, typename T_arg3>
  inline
  void Environment::callback_multifield( void* theEnv, void *rv) {
    sigc::slot3<Values, T_arg1, T_arg2, T_arg3>* cb;
    void * cbptr = get_function_context( theEnv );
    T_arg1 arg1;
    T_arg2 arg2;
    T_arg3 arg3;
    if ( cbptr ) {
      if ( get_arg_count( theEnv ) != 3 )
        throw std::logic_error( "clipsmm/mf: wrong # args on slot callback; expected 3" );
      cb = static_cast<sigc::slot3<Values, T_arg1, T_arg2, T_arg3>*>( cbptr );
      get_argument(theEnv, 1, arg1);
      get_argument(theEnv, 2, arg2);
      get_argument(theEnv, 3, arg3);
      Values v = ( *cb ) (arg1, arg2, arg3);
      set_return_values(theEnv, rv, v);
      return;
    }
    throw;
  }

  template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
  inline
  void Environment::callback_multifield( void* theEnv, void *rv) {
    sigc::slot4<Values, T_arg1, T_arg2, T_arg3, T_arg4>* cb;
    void * cbptr = get_function_context( theEnv );
    T_arg1 arg1;
    T_arg2 arg2;
    T_arg3 arg3;
    T_arg4 arg4;
    if ( cbptr ) {
      if ( get_arg_count( theEnv ) != 4 )
        throw std::logic_error( "clipsmm/mf: wrong # args on slot callback; expected 4" );
      cb = static_cast<sigc::slot4<Values, T_arg1, T_arg2, T_arg3, T_arg4>*>(cbptr);
      get_argument(theEnv, 1, arg1);
      get_argument(theEnv, 2, arg2);
      get_argument(theEnv, 3, arg3);
      get_argument(theEnv, 4, arg4);
      Values v = ( *cb ) (arg1, arg2, arg3, arg4);
      set_return_values(theEnv, rv, v);
      return;
    }
    throw;
  }

  template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4,
    typename T_arg5>
  inline
  void Environment::callback_multifield( void* theEnv, void *rv) {
      sigc::slot5<Values, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>* cb;
    void * cbptr = get_function_context( theEnv );
    T_arg1 arg1;
    T_arg2 arg2;
    T_arg3 arg3;
    T_arg4 arg4;
    T_arg5 arg5;
    if ( cbptr ) {
      if ( get_arg_count( theEnv ) != 5 )
        throw std::logic_error( "clipsmm/mf: wrong # args on slot callback; expected 5" );
      cb = static_cast<sigc::slot5<Values, T_arg1, T_arg2, T_arg3,
        T_arg4, T_arg5>*>(cbptr);
      get_argument(theEnv, 1, arg1);
      get_argument(theEnv, 2, arg2);
      get_argument(theEnv, 3, arg3);
      get_argument(theEnv, 4, arg4);
      get_argument(theEnv, 5, arg5);
      Values v = ( *cb ) (arg1, arg2, arg3, arg4, arg5);
      set_return_values(theEnv, rv, v);
      return;
    }
    throw;
  }


  template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4,
    typename T_arg5, typename T_arg6>
  inline
  void Environment::callback_multifield( void* theEnv, void *rv) {
    sigc::slot6<Values, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>* cb;
    void * cbptr = get_function_context( theEnv );
    T_arg1 arg1;
    T_arg2 arg2;
    T_arg3 arg3;
    T_arg4 arg4;
    T_arg5 arg5;
    T_arg6 arg6;
    if ( cbptr ) {
      if ( get_arg_count( theEnv ) != 6 )
        throw std::logic_error( "clipsmm/mf: wrong # args on slot callback; expected 6" );
      cb = static_cast<sigc::slot6<Values, T_arg1, T_arg2, T_arg3,
        T_arg4, T_arg5, T_arg6>*>(cbptr);
      get_argument(theEnv, 1, arg1);
      get_argument(theEnv, 2, arg2);
      get_argument(theEnv, 3, arg3);
      get_argument(theEnv, 4, arg4);
      get_argument(theEnv, 5, arg5);
      get_argument(theEnv, 6, arg6);
      Values v = ( *cb ) (arg1, arg2, arg3, arg4, arg5, arg6);
      set_return_values(theEnv, rv, v);
      return;
    }
    throw;
  }

  template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4,
    typename T_arg5, typename T_arg6, typename T_arg7>
  inline
  void Environment::callback_multifield( void* theEnv, void *rv) {
    sigc::slot7<Values, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>* cb;
    void * cbptr = get_function_context( theEnv );
    T_arg1 arg1;
    T_arg2 arg2;
    T_arg3 arg3;
    T_arg4 arg4;
    T_arg5 arg5;
    T_arg6 arg6;
    T_arg7 arg7;
    if ( cbptr ) {
      if ( get_arg_count( theEnv ) != 7 )
        throw std::logic_error( "clipsmm/mf: wrong # args on slot callback; expected 7" );
      cb = static_cast<sigc::slot7<Values, T_arg1, T_arg2, T_arg3,
        T_arg4, T_arg5, T_arg6, T_arg7>*>(cbptr);
      get_argument(theEnv, 1, arg1);
      get_argument(theEnv, 2, arg2);
      get_argument(theEnv, 3, arg3);
      get_argument(theEnv, 4, arg4);
      get_argument(theEnv, 5, arg5);
      get_argument(theEnv, 6, arg6);
      get_argument(theEnv, 7, arg7);
      Values v = ( *cb ) (arg1, arg2, arg3, arg4, arg5, arg6, arg7);
      set_return_values(theEnv, rv, v);
      return;
    }
    throw;
  }


  // **************************************************************************************

  inline
  void Environment::callback_unknown( void* theEnv, void *rv) {
    sigc::slot0<Value>* cb;
    void * cbptr = get_function_context( theEnv );
    if ( cbptr ) {
      if ( get_arg_count( theEnv ) != 0 )
        throw std::logic_error( "clipsmm/mf: wrong # args on slot callback; expected 0" );
      cb = static_cast<sigc::slot0<Value>*>( cbptr );
      Value v = ( *cb ) ();
      set_return_value(theEnv, rv, v);
      return;
    }
    throw;
  }

  template <typename T_arg1>
  inline
  void Environment::callback_unknown( void* theEnv, void *rv) {
    sigc::slot1<Value, T_arg1>* cb;
    void * cbptr = get_function_context( theEnv );
    T_arg1 arg1;
    if ( cbptr ) {
      if ( get_arg_count( theEnv ) != 1 )
        throw std::logic_error( "clipsmm/mf: wrong # args on slot callback; expected 1" );
      cb = static_cast<sigc::slot1<Value, T_arg1>*>( cbptr );
      get_argument(theEnv, 1, arg1);
      Value v = ( *cb ) (arg1);
      set_return_value(theEnv, rv, v);
      return;
    }
    throw;
  }

  template <typename T_arg1, typename T_arg2>
  inline
  void Environment::callback_unknown( void* theEnv, void *rv) {
    sigc::slot2<Value, T_arg1, T_arg2>* cb;
    void * cbptr = get_function_context( theEnv );
    T_arg1 arg1;
    T_arg2 arg2;
    if ( cbptr ) {
      if ( get_arg_count( theEnv ) != 2 )
        throw std::logic_error( "clipsmm/mf: wrong # args on slot callback; expected 2" );
      cb = static_cast<sigc::slot2<Value, T_arg1, T_arg2>*>( cbptr );
      get_argument(theEnv, 1, arg1);
      get_argument(theEnv, 2, arg2);
      Value v = ( *cb ) (arg1, arg2);
      set_return_value(theEnv, rv, v);
      return;
    }
    throw;
  }


  template <typename T_arg1, typename T_arg2, typename T_arg3>
  inline
  void Environment::callback_unknown( void* theEnv, void *rv) {
    sigc::slot3<Value, T_arg1, T_arg2, T_arg3>* cb;
    void * cbptr = get_function_context( theEnv );
    T_arg1 arg1;
    T_arg2 arg2;
    T_arg3 arg3;
    if ( cbptr ) {
      if ( get_arg_count( theEnv ) != 3 )
        throw std::logic_error( "clipsmm/mf: wrong # args on slot callback; expected 3" );
      cb = static_cast<sigc::slot3<Value, T_arg1, T_arg2, T_arg3>*>( cbptr );
      get_argument(theEnv, 1, arg1);
      get_argument(theEnv, 2, arg2);
      get_argument(theEnv, 3, arg3);
      Value v = ( *cb ) (arg1, arg2, arg3);
      set_return_value(theEnv, rv, v);
      return;
    }
    throw;
  }

  template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
  inline
  void Environment::callback_unknown( void* theEnv, void *rv) {
    sigc::slot4<Value, T_arg1, T_arg2, T_arg3, T_arg4>* cb;
    void * cbptr = get_function_context( theEnv );
    T_arg1 arg1;
    T_arg2 arg2;
    T_arg3 arg3;
    T_arg4 arg4;
    if ( cbptr ) {
      if ( get_arg_count( theEnv ) != 4 )
        throw std::logic_error( "clipsmm/mf: wrong # args on slot callback; expected 4" );
      cb = static_cast<sigc::slot4<Value, T_arg1, T_arg2, T_arg3, T_arg4>*>(cbptr);
      get_argument(theEnv, 1, arg1);
      get_argument(theEnv, 2, arg2);
      get_argument(theEnv, 3, arg3);
      get_argument(theEnv, 4, arg4);
      Value v = ( *cb ) (arg1, arg2, arg3, arg4);
      set_return_value(theEnv, rv, v);
      return;
    }
    throw;
  }

  template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4,
    typename T_arg5>
  inline
  void Environment::callback_unknown( void* theEnv, void *rv) {
      sigc::slot5<Value, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>* cb;
    void * cbptr = get_function_context( theEnv );
    T_arg1 arg1;
    T_arg2 arg2;
    T_arg3 arg3;
    T_arg4 arg4;
    T_arg5 arg5;
    if ( cbptr ) {
      if ( get_arg_count( theEnv ) != 5 )
        throw std::logic_error( "clipsmm/mf: wrong # args on slot callback; expected 5" );
      cb = static_cast<sigc::slot5<Value, T_arg1, T_arg2, T_arg3,
        T_arg4, T_arg5>*>(cbptr);
      get_argument(theEnv, 1, arg1);
      get_argument(theEnv, 2, arg2);
      get_argument(theEnv, 3, arg3);
      get_argument(theEnv, 4, arg4);
      get_argument(theEnv, 5, arg5);
      Value v = ( *cb ) (arg1, arg2, arg3, arg4, arg5);
      set_return_value(theEnv, rv, v);
      return;
    }
    throw;
  }


  template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4,
    typename T_arg5, typename T_arg6>
  inline
  void Environment::callback_unknown( void* theEnv, void *rv) {
    sigc::slot6<Value, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>* cb;
    void * cbptr = get_function_context( theEnv );
    T_arg1 arg1;
    T_arg2 arg2;
    T_arg3 arg3;
    T_arg4 arg4;
    T_arg5 arg5;
    T_arg6 arg6;
    if ( cbptr ) {
      if ( get_arg_count( theEnv ) != 6 )
        throw std::logic_error( "clipsmm/mf: wrong # args on slot callback; expected 6" );
      cb = static_cast<sigc::slot6<Value, T_arg1, T_arg2, T_arg3,
        T_arg4, T_arg5, T_arg6>*>(cbptr);
      get_argument(theEnv, 1, arg1);
      get_argument(theEnv, 2, arg2);
      get_argument(theEnv, 3, arg3);
      get_argument(theEnv, 4, arg4);
      get_argument(theEnv, 5, arg5);
      get_argument(theEnv, 6, arg6);
      Value v = ( *cb ) (arg1, arg2, arg3, arg4, arg5, arg6);
      set_return_value(theEnv, rv, v);
      return;
    }
    throw;
  }

  template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4,
    typename T_arg5, typename T_arg6, typename T_arg7>
  inline
  void Environment::callback_unknown( void* theEnv, void *rv) {
    sigc::slot7<Value, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>* cb;
    void * cbptr = get_function_context( theEnv );
    T_arg1 arg1;
    T_arg2 arg2;
    T_arg3 arg3;
    T_arg4 arg4;
    T_arg5 arg5;
    T_arg6 arg6;
    T_arg7 arg7;
    if ( cbptr ) {
      if ( get_arg_count( theEnv ) != 7 )
        throw std::logic_error( "clipsmm/mf: wrong # args on slot callback; expected 7" );
      cb = static_cast<sigc::slot7<Value, T_arg1, T_arg2, T_arg3,
        T_arg4, T_arg5, T_arg6, T_arg7>*>(cbptr);
      get_argument(theEnv, 1, arg1);
      get_argument(theEnv, 2, arg2);
      get_argument(theEnv, 3, arg3);
      get_argument(theEnv, 4, arg4);
      get_argument(theEnv, 5, arg5);
      get_argument(theEnv, 6, arg6);
      get_argument(theEnv, 7, arg7);
      Value v = ( *cb ) (arg1, arg2, arg3, arg4, arg5, arg6, arg7);
      set_return_value(theEnv, rv, v);
      return;
    }
    throw;
  }

  // **************************************************************************************


  inline
  void* Environment::strcallback( void* theEnv ) {
    sigc::slot0<std::string>* cb;
    void * cbptr = get_function_context( theEnv );
    if ( cbptr ) {
      if ( get_arg_count( theEnv ) != 0 )
        throw std::logic_error( "clipsmm/string: wrong # args on slot callback; expected 0" );
      cb = static_cast<sigc::slot0<std::string>*>( cbptr );
      return add_symbol( ( ( *cb ) ( )).c_str() );
    }
    throw;
  }

  template < typename T_arg1 >
  inline
  void* Environment::strcallback( void* theEnv ) {
    sigc::slot1<std::string,T_arg1>* cb;
    void * cbptr = get_function_context( theEnv );
    T_arg1 arg1;
    if ( cbptr ) {
      if ( get_arg_count( theEnv ) != 1 )
        throw std::logic_error( "clipsmm: wrong # args on slot callback; expected 1" );
      get_argument( theEnv, 1, arg1 );
      cb = static_cast<sigc::slot1<std::string,T_arg1>*>( cbptr );
      return add_symbol( ( ( *cb ) ( arg1 )).c_str() );
    }
    throw;
  }

  template < typename T_arg1, typename T_arg2 >
  inline
  void* Environment::strcallback( void* theEnv ) {
    sigc::slot2<std::string, T_arg1, T_arg2>* cb;
    void * cbptr = get_function_context( theEnv );
    T_arg1 arg1;
    T_arg2 arg2;
    if ( cbptr ) {
      if ( get_arg_count( theEnv ) != 2 )
        throw std::logic_error( "clipsmm: wrong # args on slot callback; expected 2" );
      get_argument( theEnv, 1, arg1 );
      get_argument( theEnv, 2, arg2 );
      cb = static_cast<sigc::slot2<std::string, T_arg1, T_arg2>*>( cbptr );
      return add_symbol( ( ( *cb ) ( arg1, arg2 )).c_str() );
    }
    throw;
  }

  template < typename T_arg1, typename T_arg2, typename T_arg3 >
  inline
  void* Environment::strcallback( void* theEnv ) {
    sigc::slot3<std::string,T_arg1,T_arg2,T_arg3>* cb;
    void * cbptr = get_function_context( theEnv );
    T_arg1 arg1;
    T_arg2 arg2;
    T_arg3 arg3;
    if ( cbptr ) {
      if ( get_arg_count( theEnv ) != 3 )
        throw std::logic_error( "clipsmm: wrong # args on slot callback; expected 3" );
      get_argument( theEnv, 1, arg1 );
      get_argument( theEnv, 2, arg2 );
      get_argument( theEnv, 3, arg3 );
      cb = static_cast<sigc::slot3<std::string, T_arg1, T_arg2,T_arg3>*>( cbptr );
      return add_symbol( ( ( *cb ) ( arg1, arg2, arg3 )).c_str() );
    }
    throw;
  }

  template < typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
  inline
  void* Environment::strcallback( void* theEnv ) {
    sigc::slot4<std::string,T_arg1,T_arg2,T_arg3,T_arg4>* cb;
    void * cbptr = get_function_context( theEnv );
    T_arg1 arg1;
    T_arg2 arg2;
    T_arg3 arg3;
    T_arg4 arg4;
    std::string s;
    if ( cbptr ) {
      if ( get_arg_count( theEnv ) != 4 )
        throw std::logic_error( "clipsmm: wrong # args on slot callback; expected 4" );
      get_argument( theEnv, 1, arg1 );
      get_argument( theEnv, 2, arg2 );
      get_argument( theEnv, 3, arg3 );
      get_argument( theEnv, 4, arg4 );
      cb = static_cast<sigc::slot4<std::string, T_arg1, T_arg2,T_arg3,T_arg4>*>( cbptr );
      s = ( *cb ) ( arg1, arg2, arg3, arg4 );
      return add_symbol( s.c_str() );
    }
    throw;
  }

  template < typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
  inline
  void* Environment::strcallback( void* theEnv ) {
    sigc::slot5<std::string,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5>* cb;
    void * cbptr = get_function_context( theEnv );
    T_arg1 arg1;
    T_arg2 arg2;
    T_arg3 arg3;
    T_arg4 arg4;
    T_arg5 arg5;
    if ( cbptr ) {
      if ( get_arg_count( theEnv ) != 5 )
        throw std::logic_error( "clipsmm: wrong # args on slot callback; expected 5" );
      get_argument( theEnv, 1, arg1 );
      get_argument( theEnv, 2, arg2 );
      get_argument( theEnv, 3, arg3 );
      get_argument( theEnv, 4, arg4 );
      get_argument( theEnv, 5, arg5 );
      cb = static_cast<sigc::slot5<std::string, T_arg1, T_arg2,T_arg3,T_arg4,T_arg5>*>( cbptr );
      return add_symbol( ( ( *cb ) ( arg1, arg2, arg3, arg4, arg5 )).c_str() );
    }
    throw;
  }

  template < typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
  inline
  void* Environment::strcallback( void* theEnv ) {
    sigc::slot6<std::string,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6>* cb;
    void * cbptr = get_function_context( theEnv );
    T_arg1 arg1;
    T_arg2 arg2;
    T_arg3 arg3;
    T_arg4 arg4;
    T_arg5 arg5;
    T_arg6 arg6;
    if ( cbptr ) {
      if ( get_arg_count( theEnv ) != 6 )
        throw std::logic_error( "clipsmm: wrong # args on slot callback; expected 6" );
      get_argument( theEnv, 1, arg1 );
      get_argument( theEnv, 2, arg2 );
      get_argument( theEnv, 3, arg3 );
      get_argument( theEnv, 4, arg4 );
      get_argument( theEnv, 5, arg5 );
      get_argument( theEnv, 6, arg6 );
      cb = static_cast<sigc::slot6<std::string, T_arg1, T_arg2,T_arg3,T_arg4,T_arg5,T_arg6>*>( cbptr );
      return add_symbol( ( ( *cb ) ( arg1, arg2, arg3, arg4, arg5, arg6 )).c_str() );
    }
    throw;
  }

  template < typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7 >
  inline
  void* Environment::strcallback( void* theEnv ) {
    sigc::slot7<std::string,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6,T_arg7>* cb;
    void * cbptr = get_function_context( theEnv );
    T_arg1 arg1;
    T_arg2 arg2;
    T_arg3 arg3;
    T_arg4 arg4;
    T_arg5 arg5;
    T_arg6 arg6;
    T_arg7 arg7;
    if ( cbptr ) {
      if ( get_arg_count( theEnv ) != 7 )
        throw std::logic_error( "clipsmm: wrong # args on slot callback; expected 7" );
      get_argument( theEnv, 1, arg1 );
      get_argument( theEnv, 2, arg2 );
      get_argument( theEnv, 3, arg3 );
      get_argument( theEnv, 4, arg4 );
      get_argument( theEnv, 5, arg5 );
      get_argument( theEnv, 6, arg6 );
      get_argument( theEnv, 7, arg7 );
      cb = static_cast<sigc::slot7<std::string, T_arg1, T_arg2,T_arg3,T_arg4,T_arg5,T_arg6,T_arg7>*>( cbptr );
      return add_symbol( ( ( *cb ) ( arg1, arg2, arg3, arg4, arg5, arg6, arg7 )).c_str() );
    }
    throw;
  }

template < typename T_return >
  inline
  bool Environment::add_function( std::string name, const sigc::slot0<T_return>& slot) {
    char retcode = get_return_code<T_return>( );
    char *argstring = get_function_restriction(name);
    sigc::slot0<T_return>* scb = new sigc::slot0<T_return>(slot);
    any holder = CLIPSPointer<sigc::slot0<T_return> >(scb);
    m_slots[name] = holder;
    return ( EnvDefineFunction2WithContext( m_cobj,
                                 const_cast<char*>( name.c_str() ),
                                 retcode,
                                 get_callback(slot),
                                 const_cast<char*>( name.c_str() ),
                                 argstring,
                                 ( void* ) scb ) );
  }

  template < typename T_return, typename T_arg1 >
  inline
  bool Environment::add_function( std::string name, const sigc::slot1<T_return, T_arg1>& slot) {
    char retcode = get_return_code<T_return>( );
    char *argstring = get_function_restriction<T_arg1>(name);
    sigc::slot1<T_return, T_arg1>* scb = new sigc::slot1<T_return, T_arg1>(slot);
    any holder = CLIPSPointer<sigc::slot1<T_return, T_arg1> >(scb);
    m_slots[name] = holder;
    return ( EnvDefineFunction2WithContext( m_cobj,
                                 const_cast<char*>( name.c_str() ),
                                 retcode,
                                 get_callback(slot),
                                 const_cast<char*>( name.c_str() ),
                                 argstring,
                                 scb ) );
  }

  template < typename T_return, typename T_arg1, typename T_arg2 >
  inline
  bool Environment::add_function( std::string name, const sigc::slot2<T_return, T_arg1, T_arg2>& slot) {
    char retcode = get_return_code<T_return>( );
    char *argstring = get_function_restriction<T_arg1,T_arg2>(name);
    sigc::slot2<T_return, T_arg1, T_arg2>* scb = new sigc::slot2<T_return, T_arg1, T_arg2>(slot);
    any holder = CLIPSPointer<sigc::slot2<T_return, T_arg1, T_arg2> >(scb);
    m_slots[name] = holder;
    return ( EnvDefineFunction2WithContext( m_cobj,
                                 const_cast<char*>( name.c_str() ),
                                 retcode,
                                 get_callback(slot),
                                 const_cast<char*>( name.c_str() ),
                                 argstring,
                                 scb ) );
  }

  template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3 >
  inline
  bool Environment::add_function( std::string name, const sigc::slot3<T_return,T_arg1,T_arg2,T_arg3>& slot) {
    char retcode = get_return_code<T_return>( );
    char *argstring = get_function_restriction<T_arg1,T_arg2,T_arg3>(name);
    sigc::slot3<T_return,T_arg1,T_arg2,T_arg3>* scb =
        new sigc::slot3<T_return,T_arg1,T_arg2,T_arg3>(slot);
    any holder = CLIPSPointer<sigc::slot3<T_return,T_arg1,T_arg2,T_arg3> >(scb);
    m_slots[name] = holder;
    return ( EnvDefineFunction2WithContext( m_cobj,
                                 const_cast<char*>( name.c_str() ),
                                 retcode,
                                 get_callback(slot),
                                 const_cast<char*>( name.c_str() ),
                                 argstring,
                                 scb )
           );
  }

  template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
  inline
  bool Environment::add_function( std::string name, const sigc::slot4<T_return,T_arg1,T_arg2,T_arg3,T_arg4>& slot) {
    char retcode = get_return_code<T_return>( );
    char *argstring = get_function_restriction<T_arg1,T_arg2,T_arg3,T_arg4>(name);
    sigc::slot4<T_return,T_arg1,T_arg2,T_arg3,T_arg4>* scb =
        new sigc::slot4<T_return,T_arg1,T_arg2,T_arg3,T_arg4>(slot);
    any holder = CLIPSPointer<sigc::slot4<T_return,T_arg1,T_arg2,T_arg3,T_arg4> >(scb);
    m_slots[name] = holder;
    return ( EnvDefineFunction2WithContext( m_cobj,
                                 const_cast<char*>( name.c_str() ),
                                 retcode,
                                 get_callback(slot),
                                 const_cast<char*>( name.c_str() ),
                                 argstring,
                                 scb )
           );
  }

  template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
  inline
  bool Environment::add_function( std::string name,
                              const sigc::slot5<T_return,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5>& slot) {
    char retcode = get_return_code<T_return>( );
    char *argstring = get_function_restriction<T_arg1,T_arg2,T_arg3,T_arg4,T_arg5>(name);
    sigc::slot5<T_return,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5>* scb =
        new sigc::slot5<T_return,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5>(slot);
    any holder = CLIPSPointer<sigc::slot5<T_return,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5> >(scb);
    m_slots[name] = holder;
    return ( EnvDefineFunction2WithContext( m_cobj,
                                 const_cast<char*>( name.c_str() ),
                                 retcode,
                                 get_callback(slot),
                                 const_cast<char*>( name.c_str() ),
                                 argstring,
                                 scb )
           );
  }

  template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
  inline
  bool Environment::add_function( std::string name,
                              const sigc::slot6<T_return,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6>& slot) {
    char retcode = get_return_code<T_return>( );
    char *argstring = get_function_restriction<T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6>(name);
    sigc::slot6<T_return,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6>* scb =
        new sigc::slot6<T_return,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6>(slot);
    any holder = CLIPSPointer<sigc::slot6<T_return,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6> >(scb);
    m_slots[name] = holder;
    return ( EnvDefineFunction2WithContext( m_cobj,
                                 const_cast<char*>( name.c_str() ),
                                 retcode,
                                 get_callback(slot),
                                 const_cast<char*>( name.c_str() ),
                                 argstring,
                                 scb )
           );
  }

  template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7 >
  inline
  bool Environment::add_function( std::string name,
                                  const sigc::slot7<T_return,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6,T_arg7>& slot) {
    char retcode = get_return_code<T_return>( );
    char *argstring = get_function_restriction<T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6,T_arg7>(name);
    sigc::slot7<T_return,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6,T_arg7>* scb =
        new sigc::slot7<T_return,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6,T_arg7>(slot);
    any holder = CLIPSPointer<sigc::slot7<T_return,T_arg1,T_arg2,T_arg3,T_arg4,T_arg5,T_arg6,T_arg7> >(scb);
    m_slots[name] = holder;
    return ( EnvDefineFunction2WithContext( m_cobj,
                                 const_cast<char*>( name.c_str() ),
                                 retcode,
                                 get_callback(slot),
                                 const_cast<char*>( name.c_str() ),
                                 argstring,
                                 scb )
           );
  }

}


#endif
