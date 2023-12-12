import angr
import claripy
import sys

# Define a function that checks if we've reached the "E" character in the maze
def is_successful(state):
    stdout_output = state.posix.dumps(sys.stdout.fileno())
    return "Congratulations".encode() in stdout_output

# Function to avoid states that reach "Try again"
def to_avoid(state):
    stdout_output = state.posix.dumps(sys.stdout.fileno())
    return "Try again".encode() in stdout_output
  

def main():
    # Load the binary
    project = angr.Project('./maze', load_options={"auto_load_libs": False})

    # Create a symbolic bitvector for the input
    input_size = 10
    input_bv = claripy.BVS('input', 8 * input_size)

    # Create a entry state with the symbolic input as an argument
    state = project.factory.entry_state(args=[project.filename, input_bv])

    # Create a simulation manager
    simgr = project.factory.simulation_manager(state)

    simgr.explore(find=is_successful, avoid=to_avoid)

    print("\n\nExploring the Maze ... \n")

    # If we found a successful state, print the input that leads to it
    if simgr.found:
        solution_state = simgr.found[0]
        solution = solution_state.solver.eval(input_bv, cast_to=bytes)
        print("Solution: ", solution)
    else:
        print("No solution found")

main()