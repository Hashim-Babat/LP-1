import streamlit as st
from datetime import datetime

# Title of the application
st.title("📝 To-Do List App")

# Explanation of the app for first-time users - Visibility and Affordance
st.write("Use this simple to-do app to add, view, and manage your tasks.")

# Initialize the session state for storing tasks
if "tasks" not in st.session_state:
    st.session_state.tasks = []

# Input field for adding new tasks
new_task = st.text_input("Add a new task:", placeholder="Enter your task here")

# Button to add the task
if st.button("Add Task"):
    if new_task:
        # Add the task with a timestamp
        task_entry = {
            "task": new_task,
            "timestamp": datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        }
        st.session_state.tasks.append(task_entry)
        st.success("Task added successfully!")  # Feedback principle
    else:
        st.warning("Please enter a task before adding.")  # Feedback for empty input

# Divider for better screen complexity handling
st.write("---")

# Display tasks with a "Done" button to remove each task - Affordance and Feedback
st.header("Your Tasks")

if st.session_state.tasks:
    for index, task in enumerate(st.session_state.tasks):
        # Show task and its timestamp
        st.write(f"{index + 1}. {task['task']} (Added on {task['timestamp']})")
        
        # Button to mark a task as completed
        if st.button(f"Mark as Done", key=index):
            st.session_state.tasks.pop(index)
            st.info("Task completed and removed!")  # Feedback after task removal
else:
    st.write("No tasks yet! Add a task to get started.")

# Footer for additional info
st.write("---")
st.caption("To-Do List App | Created with Streamlit")
