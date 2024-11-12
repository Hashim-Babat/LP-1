import streamlit as st
import pandas as pd
import numpy as np

# Set the page title and layout
st.set_page_config(page_title="Health Tracking Dashboard", layout="wide")

# Define header style
st.markdown("""
    <style>
        .main {background-color: #E0F7FA;}
        .header {font-size:30px; font-weight:bold; color:#00796B ; text-align:center;}
        .subheader {font-size:24px; font-weight:bold; color:#00796B;}
    </style>
    """, unsafe_allow_html=True)

# Title Section - Homepage
st.markdown('<div class="header">🌱 Health Tracking Dashboard</div>', unsafe_allow_html=True)
st.write("Welcome to your personalized health tracking dashboard.")

# Sidebar Navigation - Simple and intuitive
st.sidebar.title("Navigation")
page = st.sidebar.radio("Go to", ["Home", "Daily Logs", "Trends", "Goals"])

# Home Section with Key Metrics - Clean Display
if page == "Home":
    st.markdown('<div class="subheader">Daily Health Overview</div>', unsafe_allow_html=True)

    col1, col2, col3 = st.columns(3)
    with col1:
        st.metric("Steps", "6,532")
    with col2:
        st.metric("Calories Burned", "1,980 kcal")
    with col3:
        st.metric("Sleep Duration", "7h 30m")
    
    # A section for data visualization (simple placeholder)
    st.markdown('<div class="subheader">Weekly Activity</div>', unsafe_allow_html=True)
    weekly_data = pd.DataFrame(
        np.random.randint(1000, 7000, size=(7, 1)), 
        columns=["Steps"],
        index=pd.date_range("2023-10-01", periods=7)
    )
    st.line_chart(weekly_data)

# Daily Logs Section
elif page == "Daily Logs":
    st.markdown('<div class="subheader">Daily Logs</div>', unsafe_allow_html=True)
    st.write("Track your daily health metrics here.")

    # Simple data entry for logs
    st.date_input("Log Date", key="log_date")
    steps = st.number_input("Steps", min_value=0, key="steps")
    calories = st.number_input("Calories Burned", min_value=0, key="calories")
    sleep = st.number_input("Sleep Duration (hrs)", min_value=0.0, step=0.5, key="sleep")

    if st.button("Save Log"):
        st.success("Log saved successfully!")
    

# Trends Section - Shows simple progress visualization
elif page == "Trends":
    st.markdown('<div class="subheader">Progress Trends</div>', unsafe_allow_html=True)
    st.write("Visualize your progress over time with trend graphs.")

    # Placeholder trend charts
    st.subheader("Monthly Steps")
    monthly_steps = pd.DataFrame(
        np.random.randint(5000, 10000, size=(30, 1)),
        columns=["Steps"]
    )
    st.line_chart(monthly_steps)

    st.subheader("Calories Burned per Day")
    daily_calories = pd.DataFrame(
        np.random.randint(1500, 2500, size=(30, 1)),
        columns=["Calories"]
    )
    st.line_chart(daily_calories)

# Goals Section - Simple goal entry form
elif page == "Goals":
    st.markdown('<div class="subheader">Set Your Goals</div>', unsafe_allow_html=True)
    st.write("Define your personalized health goals.")

    # Goal inputs
    step_goal = st.number_input("Daily Step Goal", min_value=0, key="step_goal")
    calorie_goal = st.number_input("Daily Calorie Goal", min_value=0, key="calorie_goal")
    sleep_goal = st.number_input("Daily Sleep Goal (hrs)", min_value=0.0, step=0.5, key="sleep_goal")

    if st.button("Save Goals"):
        st.success("Goals saved successfully!")

# Footer
st.markdown("---")
st.caption("Health Tracking Dashboard | Designed for wellness")
