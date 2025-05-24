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


### Result of Sweep Process

After processing all `2n` events in the sorted list, the final value of the `switches` counter represents the total number of times the lights were turned on in the facility.

### Correctness of the Sweep-Line Approach

The correctness of this algorithm hinges on the following points:

*   **Invariant:** Throughout the sweep, just before processing any given event, the `occupancy` counter accurately reflects the number of people currently present in the facility at that specific moment in time.

*   **Identifying "Lights On" Events:** The lights are turned on precisely when an individual enters an *empty* facility.
    *   In our sweep-line algorithm, an `Entry` event is processed. If, at the moment just before this entry, the `occupancy` counter is `0`, it signifies that the facility was indeed empty.
    *   The `switches` counter is incremented *only* in this specific scenario (entry into an empty facility).

*   **Completeness and Exclusivity:**
    *   Every actual instance where the facility transitions from an empty state to a non-empty state corresponds to exactly one `Entry` event where the `occupancy` was zero immediately prior to that entry.
    *   The algorithm correctly counts one `switches++` operation for each such unique transition.
    *   Importantly, no other types of transitions (e.g., a person entering an already occupied facility, or any person exiting) cause an increment to the `switches` counter.

Therefore, the algorithm precisely and accurately returns the total number of times the lights transition from an "off" state to an "on" state.

### Complexity Analysis (Sweep-Line)

The efficiency of the sweep-line algorithm is analyzed as follows:

*   **Time Complexity:**
    *   **Sorting Events:** The primary step involves sorting the `2n` created events based on their time stamps. Using a standard comparison-based sorting algorithm, this takes `O((2n) log (2n))` time, which simplifies to **`O(n log n)`**.
    *   **Sweep:** After sorting, the algorithm performs a single linear pass through the list of `2n` events. Processing each event involves a constant amount of work (checking event type, updating counters). This sweep phase costs **`O(n)`**.
    *   **Total Time:** The overall time complexity is the sum of these two phases: `O(n log n) + O(n)`. Since `O(n log n)` grows faster than `O(n)`, the total time complexity is dominated by the sorting step, resulting in **`O(n log n)`**.

*   **Space Complexity:**
    *   The main space requirement is for storing the list of `2n` events. This requires **`O(n)`** space. Auxiliary variables like `occupancy` and `switches` use constant `O(1)` space.
Use code with caution.
Markdown
How to use this:
This snippet is designed to be a continuation of the "Algorithm 1: Sweep-Line Approach" section in the previous README.md. You would replace or append the relevant parts.
If you want this as a standalone section (perhaps if the previous README already covered the initial parts of the Sweep-Line), it would look like this:
# Sweep-Line Algorithm: Result, Correctness, and Complexity

This section details the outcome, proof of correctness, and complexity analysis for the sweep-line algorithm used to count "lights on" events based on time intervals.

## Result of Sweep Process

After processing all `2n` entry and exit events in their sorted chronological order, the final accumulated value in the `switches` counter accurately represents the total number of times the lights were turned on in the facility.

## Correctness of the Sweep-Line Approach

The algorithm's correctness is established through the following arguments:

*   **Occupancy Invariant:** A key invariant maintained throughout the sweep is that, just before processing any event, the `occupancy` counter precisely reflects the number of individuals currently within the facility at that point in time.

*   **Identifying "Lights On" Operations:** The lights are physically turned on when an individual enters a facility that was previously empty.
    *   The sweep-line algorithm models this: when an `Entry` event is encountered, if the `occupancy` counter is `0` (indicating an empty facility prior to this entry), this exact condition is identified.
    *   The `switches` counter is incremented exclusively under this "entry into empty facility" condition.

*   **Completeness and Exclusivity of Counting:**
    *   Every real-world scenario where the facility's state changes from empty to occupied corresponds to exactly one `Entry` event in our sorted list where `occupancy` was zero immediately before processing that event.
    *   The algorithm ensures that for each such distinct transition, `switches` is incremented by one.
    *   Crucially, other state transitions – such as a person entering an already occupied facility, or any person exiting (whether emptying the facility or not) – do not trigger an increment of the `switches` counter.

Based on these points, the algorithm reliably and accurately computes the total number of times the lights transition from an "off" (empty facility) state to an "on" (occupied facility) state.

## Complexity Analysis (Sweep-Line)

The computational efficiency of the sweep-line algorithm is as follows:

*   **Time Complexity:**
    *   **Sorting Phase:** The dominant operation is the initial sorting of the `2n` events by their time stamps. Using efficient comparison-based sorting algorithms (e.g., Merge Sort, Heap Sort), this step takes `O((2n) log (2n))` time, which simplifies to **`O(n log n)`**.
    *   **Sweep Phase:** Following the sort, the algorithm performs a single linear scan through the `2n` sorted events. Each event is processed in constant time (`O(1)`) involving simple comparisons and counter updates. Thus, the sweep phase takes **`O(n)`** time.
    *   **Overall Time:** The total time complexity is the sum of the sorting and sweep phases: `O(n log n) + O(n)`. As `O(n log n)` is the asymptotically larger term, the overall time complexity is **`O(n log n)`**.

*   **Space Complexity:**
    *   The primary memory usage comes from storing the list of `2n` events. This requires **`O(n)`** space. Additional variables used for counters (`occupancy`, `switches`) consume constant `O(1)` space, which is negligible compared to the event list.
