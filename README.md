# Problem Collection

This repository is a collection of small C++ subprojects that represent problems I encountered while working through code assessments during applications for senior embedded and AI software engineering roles in the United States.

Each project is intentionally compact and focused: a self-contained engineering problem, a parsing or algorithm challenge, or a systems-style exercise designed to probe correctness, design judgment, and implementation quality under interview conditions.

## Subprojects

- 01-point: a 3D point conversion and coordinate-system exercise involving Cartesian and spherical representations.
- 02-postfix: a postfix-expression consumer and evaluator focused on parsing numeric tokens and operators.
- 03-maze: a maze traversal problem centered on navigating a grid and reasoning about paths and constraints.

Together, these projects form a lightweight archive of the kinds of technical interview and assessment problems I worked through while exploring roles in embedded systems, C++, and AI-driven software engineering.

## How to Compile

This repository includes CMake workflow presets for the standard build/test flow. From the repository root, use:

```bash
cmake --preset=production
cmake --build --preset=build-production
```

For a debug build with tests enabled:

```bash
cmake --preset=debug
cmake --build --preset=build-debug
```

To run the full configured workflow as a single step:

```bash
cmake --workflow --preset=workflow-production
```

or:

```bash
cmake --workflow --preset=workflow-debug
```

The project outputs land under the `out/build/` tree, and the subproject binaries can be run from there as needed.
