import streamlit as st

# Title of the GUI
st.title("Redesigned Complex Interface")

# Principle: Simplification of the complex screen using tabs and sections
tab1, tab2, tab3 = st.tabs(["Dashboard", "Tasks", "Settings"])

# Tab 1: Dashboard
with tab1:
    st.header("Overview")
    
    # Collapsible section for summarizing key statistics
    with st.expander("Project Statistics", expanded=False):
        st.metric(label="Total Projects", value=12)
        st.metric(label="Pending Tasks", value=24)
        st.metric(label="Completed Milestones", value=5)
    
    # Principle: Feedback & Visibility - Progress bars and charts for feedback
    st.subheader("Project Progress")
    st.progress(0.7)  # 70% completion
    
    # Principle: Reducing visual complexity with side-by-side columns
    col1, col2 = st.columns(2)
    
    with col1:
        st.write("Upcoming Deadlines")
        st.write("1. Project Alpha - Oct 20, 2024")
        st.write("2. Project Beta - Nov 12, 2024")
        
    with col2:
        st.write("Team Members")
        st.write("1. John Doe")
        st.write("2. Jane Smith")
        st.write("3. Alan Brown")

# Tab 2: Task Management
with tab2:
    st.header("Manage Your Tasks")
    
    # Collapsible section to declutter the screen
    with st.expander("Add New Task"):
        task = st.text_input("Task Name")
        task_desc = st.text_area("Task Description")
        priority = st.selectbox("Priority", ["High", "Medium", "Low"])
        if st.button("Add Task"):
            if task:
                st.success(f"Task '{task}' added successfully with priority {priority}")
            else:
                st.error("Task Name cannot be empty!")
    
    # Task list with priority indicators for a clearer view
    st.subheader("Your Tasks")
    task_list = [
        {"name": "Task A", "priority": "High"},
        {"name": "Task B", "priority": "Medium"},
        {"name": "Task C", "priority": "Low"},
    ]
    
    for task_item in task_list:
        priority_color = "🔴" if task_item["priority"] == "High" else "🟡" if task_item["priority"] == "Medium" else "🟢"
        st.write(f"{priority_color} {task_item['name']} ({task_item['priority']})")
    
# Tab 3: Settings
with tab3:
    st.header("User Settings")
    
    # Collapsible options to reduce screen complexity
    with st.expander("Update Profile"):
        username = st.text_input("Username", value="JohnDoe")
        email = st.text_input("Email", value="john.doe@example.com")
        if st.button("Save Settings"):
            st.success("Settings updated successfully!")
    
    with st.expander("Notification Preferences"):
        email_notif = st.checkbox("Receive Email Notifications", value=True)
        push_notif = st.checkbox("Receive Push Notifications", value=False)
        if st.button("Save Preferences"):
            st.success("Notification preferences updated!")

# Sidebar for additional controls
st.sidebar.header("Navigation")
st.sidebar.write("Use the tabs above to navigate through the interface.")
st.sidebar.write("You can customize the content based on your preferences.")
