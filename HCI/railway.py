import streamlit as st
import pandas as pd

# Apply custom background colors using CSS
st.markdown(
    """
    <style>
    /* Customize the color of buttons */
    .stButton>button {
        background-color: #40AF50; /* Green button */
        color: white;
        border-radius: 5px;
        border: none;
        padding: 10px 20px;
    }
    </style>
    """,
    unsafe_allow_html=True
)

# Title and main header
st.title("Railway Management System")
st.header("Welcome to the    Railway Management System")

# Sidebar navigation
menu = st.sidebar.radio("Select an Option", ["PNR Status Check", "Seat Availability", "Book Ticket", "Train Schedules", "Fare Inquiry", "Cancel Ticket", "Feedback"])

# Session state to hold booking details
if "booking_details" not in st.session_state:
    # Add 5 random person details as default data
    st.session_state.booking_details = [
        {"Name": "Ketan Bajaj", "Age": 29, "Train Number": "12345", "Date": "2023-07-01", "Class": "3A"},
        {"Name": "Niranjan Dangi", "Age": 34, "Train Number": "54321", "Date": "2021-04-03", "Class": "Sleeper"},
        {"Name": "Anish Dabhane", "Age": 25, "Train Number": "67890", "Date": "2024-01-05", "Class": "2A"},
        {"Name": "Hashim Babat", "Age": 21, "Train Number": "98765", "Date": "2022-12-07", "Class": "1A"},
        {"Name": "Aarya Bhave"  , "Age": 31, "Train Number": "24680", "Date": "2020-11-09", "Class": "Sleeper"}
    ]

if menu == "PNR Status Check":
    st.subheader("Check Your PNR Status")
    pnr = st.text_input("Enter your PNR Number:")
    if st.button("Check Status"):
        if pnr.isdigit() and len(pnr) == 10:
            st.success(f"Checking PNR status for {pnr}... [Dummy Response]")
        else:
            st.error("Invalid PNR number. Please enter a 10-digit number.")

elif menu == "Seat Availability":
    st.subheader("Check Seat Availability")
    train_no = st.text_input("Enter Train Number:")
    date = st.date_input("Select Date:")
    travel_class = st.selectbox("Select Class", ["Sleeper", "3A", "2A", "1A"])
    if st.button("Check Availability"):
        if train_no:
            st.info(f"Checking seat availability for Train {train_no} on {date} in {travel_class} class... [Dummy Response]")
        else:
            st.warning("Please enter a valid train number")

elif menu == "Book Ticket":
    st.subheader("Book Your Ticket")
    with st.form("booking_form"):
        name = st.text_input("Passenger Name")
        age = st.number_input("Age", min_value=0, max_value=100)
        train_no = st.text_input("Enter Train Number")
        date = st.date_input("Select Date")
        travel_class = st.selectbox("Select Class", ["Sleeper", "3A", "2A", "1A"])
        submit_button = st.form_submit_button("Book Ticket")
        if submit_button:
            if name and train_no:
                # Add booking details to the session state
                st.session_state.booking_details.append({
                    "Name": name,
                    "Age": age,
                    "Train Number": train_no,
                    "Date": str(date),
                    "Class": travel_class
                })
                st.success(f"Ticket booked successfully for {name} on Train {train_no} on {date} in {travel_class} class.")
            else:
                st.warning("Please fill in all required fields")

    # Display booking details in a table if there are any
    if st.session_state.booking_details:
        st.subheader("Booked Ticket Details")
        st.table(pd.DataFrame(st.session_state.booking_details))

elif menu == "Train Schedules":
    st.subheader("Check Train Schedule")
    train_no = st.text_input("Enter Train Number:")
    if st.button("Show Schedule"):
        if train_no:
            st.info(f"Displaying schedule for Train {train_no}... [Dummy Response]")
        else:
            st.warning("Please enter a valid train number")

elif menu == "Fare Inquiry":
    st.subheader("Check Fare Details")
    train_no = st.text_input("Enter Train Number:")
    source = st.text_input("Enter Source Station:")
    destination = st.text_input("Enter Destination Station:")
    travel_class = st.selectbox("Select Class", ["Sleeper", "3A", "2A", "1A"])
    if st.button("Check Fare"):
        if train_no and source and destination:
            st.info(f"Checking fare for Train {train_no} from {source} to {destination} in {travel_class} class... [Dummy Response]")
        else:
            st.warning("Please fill in all required fields")

elif menu == "Cancel Ticket":
    st.subheader("Cancel Your Ticket")
    pnr = st.text_input("Enter your PNR Number:")
    if st.button("Cancel Ticket"):
        if pnr.isdigit() and len(pnr) == 10:
            st.success(f"Ticket with PNR {pnr} has been cancelled... [Dummy Response]")
        else:
            st.error("Invalid PNR number. Please enter a 10-digit number.")

elif menu == "Feedback":
    st.subheader("We value your feedback")
    feedback = st.text_area("Please provide your feedback about your journey:")
    rating = st.radio("Rate your train journey:", ["Very bad", "Satisfactory", "Good", "Best", "Overwhelmed"])
    if st.button("Submit Feedback"):
        if feedback:
            st.success("Thank you for your feedback!")
            st.info(f"Your rating: {rating}")
        else:
            st.warning("Please provide feedback before submitting.")

# Footer or additional section
st.write("---")
st.caption("Railway Management System | Developed for educational purposes")
    