// To use, run:
// clang least_cost_for_target.c; ./a.out
// or
// gcc least_cost_for_target.c; ./a.out
//
#include "optimiser.c"

static void setup_run() {
  printf("Optimising for minimum cost, that also meets 80%% emissions reduction target\n\n");
}

// This is the key optimisation method, which defined what GOOD is.
// Must return an int, with a higher number meaning more fit.
static int calculate_fitness_of(Candidate candidate) {
  int emissions_reduction, cost;
  reset();
  set_input_choices(candidate.choices);
  emissions_reduction = (int) (output_emissions_percentage_reduction().number * 100);
  cost = (int) (output_costpercapita_npv_point().number);
  // If emissions reduction is less than 80, count that as fitness
  if(emissions_reduction < 80) { return emissions_reduction; }
  // Subtract cost per capita from 1 million so that positive numbers are fitter
  return 1e6-cost;
}

// The fitness often won't be very meaningful, so when presenting results can be
// usefull to show more data about the candidate
static void describe(Candidate candidate) {
  reset();
  set_input_choices(candidate.choices);
  printf("Reduction in emissions 1990-2050: %2.0f%% NPV of cost per capita: £%.0f 2010-2050", output_emissions_percentage_reduction().number * 100.0, output_costpercapita_npv_point().number);
}

