# Algorithms for Counting "Lights On" Events / Merged Interval Components

This document describes two efficient algorithms to solve the problem of determining how many times a "lights on" event occurs, given a set of time intervals representing when individuals are present. This is equivalent to counting the number of connected components in the union of these time intervals.

## Problem Definition

Given `n` individuals, where each individual `i` is present in a facility (e.g., a gym) during a time interval `(a_i, b_i)`. We assume all start times `a_i` and end times `b_i` are distinct. The goal is to count the number of times the lights in the facility are turned on. The lights turn on when the first person enters an empty facility and turn off when the last person leaves a facility (making it empty again).

---

## Algorithm 1: Sweep-Line Approach

This approach models the problem by processing events along a timeline.

### 1. Event Creation
For each person `i` with interval `(a_i, b_i)`, create two events:
*   **Entry Event:** At time `a_i`, with a "weight" of `+1`.
*   **Exit Event:** At time `b_i`, with a "weight" of `-1`.

This results in `2n` events in total.

### 2. Sorting Events
Collect all `2n` events into a single list and sort them by their time attribute. Since all `a_i` and `b_i` are distinct, there are no ties in time for different event points.

### 3. Sweep Process
Maintain two integer counters:
*   `occupancy = 0`: Tracks the number of people currently in the facility.
*   `switches = 0`: Counts the number of times the lights were turned on.

Scan the sorted events in increasing order of time:

```text
for each event e in time-order:
  if e is an Entry event (+1):
    if occupancy == 0:  // Facility was empty before this person entered
      switches = switches + 1
    occupancy = occupancy + 1
  else if e is an Exit event (-1):
    occupancy = occupancy - 1
    // No action on 'switches' when someone exits
