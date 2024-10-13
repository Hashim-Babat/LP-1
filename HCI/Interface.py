import streamlit as st

# Principle: Visibility - Ensuring UI elements are visible and understandable
st.title("Project Management Dashboard")

# Principle: Affordance - The buttons clearly show that they can be clicked (interactivity)
st.header("Task Manager")

# Principle: Consistency - Using consistent labels and design patterns
task = st.text_input("Enter a new task:")

# Principle: Feedback - Giving immediate response when user interacts with the input
if task:
    st.success(f"Task '{task}' added successfully!")  # Positive feedback for task creation

# Principle: User Control - Allow users to undo an action
if st.button("Undo"):
    st.info("Last action undone!")  # Feedback for undoing

# Principle: Error Prevention - Prevent invalid inputs with clear constraints
task_length = len(task)
if task_length > 50:
    st.warning("Task description too long! Maximum 50 characters allowed.")  # Prevent error with warning

# Principle: Feedback - Immediate feedback for task length
st.write(f"Current task length: {task_length} characters.")

# Principle: User Control and Flexibility - Allowing users to choose a project
st.sidebar.header("Project Selector")
project = st.sidebar.selectbox("Select a project:", ["Project Alpha", "Project Beta", "Project Gamma"])

# Principle: Visibility - Clearly showing current project context
st.write(f"Tasks for project: {project}")

# Principle: Affordance and Error Prevention - A button for task submission with feedback and prevention of empty submissions
if st.button("Submit Task"):
    if not task:
        st.error("Task cannot be empty!")  # Prevent empty submission
    else:
        st.success(f"Task '{task}' submitted to {project}!")  # Positive feedback
