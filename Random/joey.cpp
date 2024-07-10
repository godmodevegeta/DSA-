<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Employee Access</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            margin: 0;
            background-color: #f0f0f0;
        }

        .container {
            background-color: #ffffff;
            border-radius: 8px;
            box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
            width: 90%;
            max-width: 400px;
            animation: fadeIn 1s ease-in-out;
            overflow: hidden;
        }

        @keyframes fadeIn {
            from { opacity: 0; }
            to { opacity: 1; }
        }

        .top-bar {
            background-color: #007bff;
            color: white;
            padding: 15px;
            text-align: center;
            font-size: 24px;
            font-weight: bold;
            width: 100%;
            box-sizing: border-box;
            animation: slideIn 1s ease-in-out;
        }

        @keyframes slideIn {
            from { transform: translateY(-100%); }
            to { transform: translateY(0); }
        }

        .content {
            padding: 20px;
            box-sizing: border-box;
        }

        .input-group {
            margin-bottom: 15px;
        }

        .input-group label {
            display: block;
            margin-bottom: 5px;
            font-weight: bold;
        }

        .input-group input {
            width: calc(100% - 10px);
            padding: 8px;
            border: 1px solid #ccc;
            border-radius: 4px;
            margin-right: 10px;
        }

        .input-group-buttons {
            display: flex;
            justify-content: space-between;
            margin-bottom: 15px;
        }

        .input-group-buttons button {
            width: 48%;
            padding: 10px;
            background-color: #007bff;
            color: white;
            border: none;
            border-radius: 4px;
            cursor: pointer;
            font-size: 16px;
        }

        .input-group-buttons button:hover {
            background-color: #0056b3;
        }

        .message {
            margin-top: 20px;
            padding: 10px;
            border-radius: 4px;
            display: none;
        }

        .message.success {
            background-color: #d4edda;
            color: #155724;
        }

        .message.error {
            background-color: #f8d7da;
            color: #721c24;
        }

        .verify-next {
            text-align: center;
            margin-top: 20px;
        }

        .verify-next button {
            padding: 10px 20px;
            background-color: #007bff;
            color: white;
            border: none;
            border-radius: 4px;
            cursor: pointer;
            font-size: 16px;
        }

        .verify-next button:hover {
            background-color: #0056b3;
        }

        .spacer {
            height: 20px;
        }

        @media (max-width: 768px) {
            .container {
                width: 90%;
                max-width: 90%;
            }

            .input-group-buttons {
                flex-direction: column;
            }

            .input-group-buttons button {
                width: 100%;
                margin-bottom: 10px;
            }

            .verify-next button {
                width: 100%;
            }
        }

        @media (max-width: 480px) {
            .top-bar {
                font-size: 20px;
                padding: 10px;
            }

            .input-group input {
                width: calc(100% - 8px);
            }

            .input-group label {
                font-size: 14px;
            }

            .input-group-buttons button {
                font-size: 14px;
                padding: 8px;
            }

            .verify-next button {
                font-size: 14px;
                padding: 8px;
            }
        }
    </style>
</head>
<body>
    <div class="container">
        <div class="top-bar">London Cafe Access</div>
        <div class="content">
            <div id="initialInput" class="input-group">
                <label for="employeeId">Employee ID</label>
                <input type="text" id="employeeId" placeholder="Enter Employee ID">
            </div>
            <div id="initialButtons" class="input-group input-group-buttons">
                <button onclick="enterAsHost(event)">Enter as Host</button>
                <button onclick="enterAsGuest(event)">Enter as Guest</button>
            </div>
            <div id="message" class="message"></div>
            <div id="employeeDetails" class="input-group" style="display: none;">
                <label for="employeeName">Employee Name</label>
                <input type="text" id="employeeName" readonly>
            </div>
            <div id="employeeDepartment" class="input-group" style="display: none;">
                <label for="employeeDept">Department</label>
                <input type="text" id="employeeDept" readonly>
            </div>
            <div id="employeePosition" class="input-group" style="display: none;">
                <label for="employeePos">Position</label>
                <input type="text" id="employeePos" readonly>
            </div>
            <div class="spacer"></div>
            <div class="verify-next" id="verifyNextDiv">
                <button onclick="location.reload()">Verify Next Person</button>
            </div>
        </div>
    </div>

    <script>
        document.addEventListener("DOMContentLoaded", function () {
            // Initialize event listeners or any required setup here
        });

        function enterAsGuest(event) {
            event.preventDefault();
            handleAccessCheck(false);
        }

        function enterAsHost(event) {
            event.preventDefault();
            handleAccessCheck(true);
        }

        function handleAccessCheck(isHost) {
            const employeeId = document.getElementById('employeeId').value;
            const messageDiv = document.getElementById('message');
            const employeeDetailsDiv = document.getElementById('employeeDetails');
            const employeeDepartmentDiv = document.getElementById('employeeDepartment');
            const employeePositionDiv = document.getElementById('employeePosition');
            const employeeNameInput = document.getElementById('employeeName');
            const employeeDeptInput = document.getElementById('employeeDept');
            const employeePosInput = document.getElementById('employeePos');
            const initialInputDiv = document.getElementById('initialInput');
            const initialButtonsDiv = document.getElementById('initialButtons');

            // Clear previous messages and details
            messageDiv.style.display = 'none';
            employeeDetailsDiv.style.display = 'none';
            employeeDepartmentDiv.style.display = 'none';
            employeePositionDiv.style.display = 'none';
            messageDiv.classList.remove('success', 'error');

            if (employeeId.trim() === "") {
                messageDiv.textContent = 'Please enter a valid Employee ID';
                messageDiv.classList.add('error');
                messageDiv.style.display = 'block';
                return;
            }

            // Simulate a database check (replace with actual API call)
            const employees = [
                { id: '123', name: 'John Doe', department: 'Sales', position: 'Manager', hasAccess: true },
                { id: '456', name: 'Jane Smith', department: 'Marketing', position: 'Executive', hasAccess: false },
                { id: '789', name: 'Guest User', department: 'HR', position: 'Assistant', hasAccess: true }
            ];

            const employee = employees.find(emp => emp.id === employeeId);

            if (!employee) {
                messageDiv.textContent = 'Invalid Employee ID';
                messageDiv.classList.add('error');
                messageDiv.style.display = 'block';
                return;
            }

            initialInputDiv.style.display = 'none';
            initialButtonsDiv.style.display = 'none';
            employeeNameInput.value = employee.name;
            employeeDeptInput.value = employee.department;
            employeePosInput.value = employee.position;
            employeeDetailsDiv.style.display = 'block';
            employeeDepartmentDiv.style.display = 'block';
            employeePositionDiv.style.display = 'block';

            if (isHost && !employee.hasAccess) {
                messageDiv.textContent = 'Access Denied';
                messageDiv.classList.add('error');
            } else {
                messageDiv.textContent = isHost ? 'Access Granted' : 'Cafeteria access has been granted';
                messageDiv.classList.add('success');
            }
            messageDiv.style.display = 'block';

            showVerifyNextButton();
        }

        function showVerifyNextButton() {
            document.getElementById('verifyNextDiv').style.display = 'block';
        }
    </script>
</body>
</html>


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Employee Access</title>
    <link href="https://fonts.googleapis.com/css2?family=Open+Sans:wght@400;600&family=Playfair+Display:wght@700&display=swap" rel="stylesheet">
    <style>
        body {
            font-family: 'Open Sans', sans-serif;
            display: flex;
            flex-direction: column;
            align-items: center;
            height: 100vh;
            margin: 0;
            background-color: #f0f0f0;
        }
        .header {
            background-color: rgba(0,20,96,0.8);
            color: white;
            width: 100%;
            padding: 15px;
            box-sizing: border-box;
            font-size: 24px;
            font-weight: bold;
            position: fixed;
            top: 0;
            z-index: 1000;
            box-shadow: 0 4px 8px rgba(0, 0, 0, 0.2);
            
        }
        .container {
            background-color: #ffffff;
            border-radius: 8px;
            box-shadow: 0 4px 15px rgba(0, 0, 0, 0.2);
            width: 90%;
            max-width: 400px;
            animation: fadeIn 1s ease-in-out;
            overflow: hidden;
            margin-top: 80px; /* Adjust for the header */
        }

        @keyframes fadeIn {
            from { opacity: 0; }
            to { opacity: 1; }
        }

        .top-bar {
            background-color: rgba(0,20,96,0.8);
            color: white;
            padding: 15px;
            text-align: center;
            font-size: 24px;
            font-weight: bold;
            width: 100%;
            box-sizing: border-box;
            animation: slideIn 1s ease-in-out;
            box-shadow: 0 2px 4px rgba(0, 0, 0, 0.2);
            
        }

        @keyframes slideIn {
            from { transform: translateY(-100%); }
            to { transform: translateY(0); }
        }

        .content {
            padding: 20px;
            box-sizing: border-box;
            animation: contentFadeIn 1s ease-in-out;
        }

        @keyframes contentFadeIn {
            from { opacity: 0; transform: scale(0.95); }
            to { opacity: 1; transform: scale(1); }
        }

        .input-group {
            margin-bottom: 15px;
        }

        .input-group label {
            display: block;
            margin-bottom: 5px;
            font-weight: bold;
        }

        .input-group input {
            width: calc(100% - 10px);
            padding: 8px;
            border: 1px solid #ccc;
            border-radius: 4px;
            margin-right: 10px;
            box-shadow: inset 0 1px 3px rgba(0, 0, 0, 0.1);
        }

        .input-group-buttons {
            display: flex;
            justify-content: space-between;
            margin-bottom: 15px;
        }

        .input-group-buttons button {
            width: 48%;
            padding: 10px;
            background-color: rgba(0,20,96,0.8);
            color: white;
            border: none;
            border-radius: 4px;
            cursor: pointer;
            font-size: 16px;
            transition: background-color 0.3s ease;
            box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);
            font-family: 'Open Sans', sans-serif;
            font-weight: 600;
        }

        .input-group-buttons button:hover {
            background-color: #16206a;
        }

        .message {
            margin-top: 20px;
            padding: 10px;
            border-radius: 4px;
            display: none;
        }

        .message.success {
            background-color: #d4edda;
            color: #155724;
        }

        .message.error {
            background-color: #f8d7da;
            color: #721c24;
        }

        .verify-next {
            display: none;
            text-align: center;
            margin-top: 20px;
        }

        .verify-next button {
            padding: 10px 20px;
            background-color: rgba(0,20,96,0.8);
            color: white;
            border: none;
            border-radius: 4px;
            cursor: pointer;
            font-size: 16px;
            transition: background-color 0.3s ease;
            box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);
            font-family: 'Open Sans', sans-serif;
            font-weight: 600;
        }

        .verify-next button:hover {
            background-color: #16206a;
        }

        .spacer {
            height: 20px;
        }

        .loader {
            border: 4px solid #f3f3f3;
            border-radius: 50%;
            border-top: 4px solid #1b2781;
            width: 30px;
            height: 30px;
            animation: spin 2s linear infinite;
            display: none;
            margin: 0 auto;
        }

        @keyframes spin {
            0% { transform: rotate(0deg); }
            100% { transform: rotate(360deg); }
        }

        .download-log {
            position: relative;
            top: 60px;
            float: left;
        }

        .download-log button {
            padding: 10px 20px;
            background-color: rgba(0,20,96,0.8);
            color: white;
            border: none;
            border-radius: 4px;
            cursor: pointer;
            font-size: 16px;
            transition: background-color 0.3s ease;
            box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);
            font-family: 'Open Sans', sans-serif;
            font-weight: 600;
        }

        .download-log button:hover {
            background-color: #16206a;
        }

        @media (max-width: 768px) {
            .container {
                width: 90%;
                max-width: 90%;
            }

            .input-group-buttons {
                flex-direction: column;
            }

            .input-group-buttons button {
                width: 100%;
                margin-bottom: 10px;
            }

            .verify-next button {
                width: 100%;
            }
        }

        @media (max-width: 480px) {
            .top-bar {
                font-size: 20px;
                padding: 10px;
            }

            .input-group input {
                width: calc(100% - 8px);
            }

            .input-group label {
                font-size: 14px;
            }

            .input-group-buttons button {
                font-size: 14px;
                padding: 8px;
            }

            .verify-next button {
                font-size: 14px;
                padding: 8px;
            }

            .download-log button {
                font-size: 14px;
                padding: 8px;
            }
        }
    </style>
</head>
<body>
    <div class="header">JP Morgan Chase | Partner Dining Usecase</div>
    <br/>
    <br/>
    <div class="download-log ">
        <button onclick="downloadLog()">Download Log</button>
    </div>
    <div class="container">
        <div class="top-bar">London Cafe Access</div>
        <div class="content">
            <div class="input-group" id="employeeIdGroup">
                <label for="employeeId">Employee ID</label>
                <input type="text" id="employeeId" placeholder="Enter Employee ID">
                <br/>
                <br/>
            </div>
            
            <div class="input-group input-group-buttons" id="buttonsGroup">
                <button onclick="enterAsHost()">Enter as Host</button>
                <button onclick="enterAsGuest()">Enter as Guest</button>
            </div>
            <div id="message" class="message"></div>
            <div class="loader" id="loader"></div>
            <br/>
            <br/>
            <div id="employeeDetails" class="input-group" style="display: none;">
                <label for="employeeName">Employee Name</label>
                <input type="text" id="employeeName" readonly>
            </div>
            <div id="employeeDepartment" class="input-group" style="display: none;">
                <label for="employeeDept">Department</label>
                <input type="text" id="employeeDept" readonly>
            </div>
            <div id="employeePosition" class="input-group" style="display: none;">
                <label for="employeePos">Position</label>
                <input type="text" id="employeePos" readonly>
            </div>
        </div>
        <div class="verify-next" id="verifyNextDiv">
            <button onclick="resetForm()">Verify Next</button>
        </div>
    </div>
    

    <script>
        const logEntries = JSON.parse(localStorage.getItem('logEntries')) || [];

        function enterAsGuest() {
            const employeeId = sanitizeInput(document.getElementById('employeeId').value);
            const messageDiv = document.getElementById('message');
            const loader = document.getElementById('loader');
            const employeeDetailsDiv = document.getElementById('employeeDetails');
            const employeeDepartmentDiv = document.getElementById('employeeDepartment');
            const employeePositionDiv = document.getElementById('employeePosition');
            const employeeNameInput = document.getElementById('employeeName');
            const employeeDeptInput = document.getElementById('employeeDept');
            const employeePosInput = document.getElementById('employeePos');
            const employeeIdGroup = document.getElementById('employeeIdGroup');
            const buttonsGroup = document.getElementById('buttonsGroup');

            // Hide input field and buttons
            employeeIdGroup.style.display = 'none';
            buttonsGroup.style.display = 'none';

            // Clear previous messages and details
            messageDiv.style.display = 'none';
            employeeDetailsDiv.style.display = 'none';
            employeeDepartmentDiv.style.display = 'none';
            employeePositionDiv.style.display = 'none';
            messageDiv.classList.remove('success', 'error');

            if (employeeId.trim() === "") {
                messageDiv.textContent = 'Please enter a valid Employee ID';
                messageDiv.classList.add('error');
                messageDiv.style.display = 'block';
                showVerifyNextButton();
                return;
            }

            // Show loader
            loader.style.display = 'block';

            // Simulate a database check (replace with actual API call)
            fetchEmployeeDetails(employeeId, function(employee) {
                // Hide loader
                loader.style.display = 'none';

                if (!employee) {
                    messageDiv.textContent = 'Please enter valid Employee ID';
                    messageDiv.classList.add('error');
                    messageDiv.style.display = 'block';
                } else {
                    employeeNameInput.value = employee.name;
                    employeeDeptInput.value = employee.department;
                    employeePosInput.value = employee.position;
                    employeeDetailsDiv.style.display = 'block';
                    employeeDepartmentDiv.style.display = 'block';
                    employeePositionDiv.style.display = 'block';
                    messageDiv.textContent = 'Cafeteria access has been granted';
                    messageDiv.classList.add('success');
                    messageDiv.style.display = 'block';

                    // Update log
                    updateLog(employeeId, employee.name, 'Guest');
                }

                showVerifyNextButton();
            });
        }

        function enterAsHost() {
            const employeeId = sanitizeInput(document.getElementById('employeeId').value);
            const messageDiv = document.getElementById('message');
            const loader = document.getElementById('loader');
            const employeeDetailsDiv = document.getElementById('employeeDetails');
            const employeeDepartmentDiv = document.getElementById('employeeDepartment');
            const employeePositionDiv = document.getElementById('employeePosition');
            const employeeNameInput = document.getElementById('employeeName');
            const employeeDeptInput = document.getElementById('employeeDept');
            const employeePosInput = document.getElementById('employeePos');
            const employeeIdGroup = document.getElementById('employeeIdGroup');
            const buttonsGroup = document.getElementById('buttonsGroup');

            // Hide input field and buttons
            employeeIdGroup.style.display = 'none';
            buttonsGroup.style.display = 'none';

            // Clear previous messages and details
            messageDiv.style.display = 'none';
            employeeDetailsDiv.style.display = 'none';
            employeeDepartmentDiv.style.display = 'none';
            employeePositionDiv.style.display = 'none';
            messageDiv.classList.remove('success', 'error');

            if (employeeId.trim() === "") {
                messageDiv.textContent = 'Please enter a valid Employee ID';
                messageDiv.classList.add('error');
                messageDiv.style.display = 'block';
                showVerifyNextButton();
                return;
            }

            // Show loader
            loader.style.display = 'block';

            // Simulate a database check (replace with actual API call)
            fetchEmployeeDetails(employeeId, function(employee) {
                // Hide loader
                loader.style.display = 'none';

                if (!employee) {
                    messageDiv.textContent = 'Please enter valid Employee ID';
                    messageDiv.classList.add('error');
                    messageDiv.style.display = 'block';
                } else if (!employee.hasAccess) {
                    messageDiv.textContent = 'Access Denied';
                    messageDiv.classList.add('error');
                    messageDiv.style.display = 'block';
                } else {
                    employeeNameInput.value = employee.name;
                    employeeDeptInput.value = employee.department;
                    employeePosInput.value = employee.position;
                    employeeDetailsDiv.style.display = 'block';
                    employeeDepartmentDiv.style.display = 'block';
                    employeePositionDiv.style.display = 'block';
                    messageDiv.textContent = 'Access Granted';
                    messageDiv.classList.add('success');
                    messageDiv.style.display = 'block';

                    // Update log
                    updateLog(employeeId, employee.name, 'Host');
                }

                showVerifyNextButton();
            });
        }

        function updateLog(id, name, type) {
            logEntries.push({ id, name, type });
            localStorage.setItem('logEntries', JSON.stringify(logEntries));
        }

        function downloadLog() {
            const csvContent = "data:text/csv;charset=utf-8,"
                + "Employee ID,Name,Type\n"
                + logEntries.map(entry => `${entry.id},${entry.name},${entry.type}`).join("\n");

            const encodedUri = encodeURI(csvContent);
            const link = document.createElement("a");
            link.setAttribute("href", encodedUri);
            link.setAttribute("download", "employee_log.csv");
            document.body.appendChild(link);

            link.click();
            document.body.removeChild(link);
        }

        function showVerifyNextButton() {
            const verifyNextDiv = document.getElementById('verifyNextDiv');
            verifyNextDiv.style.display = 'block';
        }

        function resetForm() {
            document.getElementById('employeeId').value = '';
            document.getElementById('employeeName').value = '';
            document.getElementById('employeeDept').value = '';
            document.getElementById('employeePos').value = '';
            document.getElementById('message').style.display = 'none';
            document.getElementById('employeeDetails').style.display = 'none';
            document.getElementById('employeeDepartment').style.display = 'none';
            document.getElementById('employeePosition').style.display = 'none';
            document.getElementById('verifyNextDiv').style.display = 'none';
            document.getElementById('employeeIdGroup').style.display = 'block';
            document.getElementById('buttonsGroup').style.display = 'flex';
        }

        function sanitizeInput(input) {
            const div = document.createElement('div');
            div.textContent = input;
            return div.innerHTML;
        }

        function fetchEmployeeDetails(employeeId, callback) {
            // Replace this with an actual API call
            const employees = [
                { id: '123', name: 'John Doe', department: 'Sales', position: 'Manager', hasAccess: true },
                { id: '456', name: 'Jane Smith', department: 'Marketing', position: 'Executive', hasAccess: false },
                { id: '789', name: 'Guest User', department: 'HR', position: 'Assistant', hasAccess: true }
            ];
            
            const employee = employees.find(emp => emp.id === employeeId);
            setTimeout(() => callback(employee), 1000); // Simulate async API call
        }
    </script>
</body>
</html>


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Employee Access</title>
    <link href="https://fonts.googleapis.com/css2?family=Open+Sans:wght@400;600&family=Playfair+Display:wght@700&display=swap" rel="stylesheet">
    <style>
        body {
            font-family: 'Open Sans', sans-serif;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            margin: 0;
            background-color: #f0f0f0;
            overflow: hidden;
        }
        .header {
            background-color: rgba(0,20,96,0.8);
            color: white;
            width: 100%;
            padding: 15px;
            text-align: center;
            box-sizing: border-box;
            font-size: 24px;
            font-weight: bold;
            position: fixed;
            top: 0;
            z-index: 1000;
            box-shadow: 0 4px 8px rgba(0, 0, 0, 0.2);
        }
        .container {
            background-color: #ffffff;
            border-radius: 8px;
            box-shadow: 0 4px 15px rgba(0, 0, 0, 0.2);
            width: 90%;
            max-width: 400px;
            animation: fadeIn 1s ease-in-out;
            overflow: hidden;
            margin-top: 80px; /* Adjust for the header */
        }

        @keyframes fadeIn {
            from { opacity: 0; }
            to { opacity: 1; }
        }

        .top-bar {
            background-color: rgba(0,20,96,0.8);
            color: white;
            padding: 15px;
            text-align: center;
            font-size: 24px;
            font-weight: bold;
            width: 100%;
            box-sizing: border-box;
            animation: slideIn 1s ease-in-out;
            box-shadow: 0 2px 4px rgba(0, 0, 0, 0.2);
        }

        @keyframes slideIn {
            from { transform: translateY(-100%); }
            to { transform: translateY(0); }
        }

        .content {
            padding: 20px;
            box-sizing: border-box;
            animation: contentFadeIn 1s ease-in-out;
        }

        @keyframes contentFadeIn {
            from { opacity: 0; transform: scale(0.95); }
            to { opacity: 1; transform: scale(1); }
        }

        .input-group {
            margin-bottom: 15px;
        }

        .input-group label {
            display: block;
            margin-bottom: 5px;
            font-weight: bold;
        }

        .input-group input {
            width: calc(100% - 10px);
            padding: 8px;
            border: 1px solid #ccc;
            border-radius: 4px;
            margin-right: 10px;
            box-shadow: inset 0 1px 3px rgba(0, 0, 0, 0.1);
        }

        .input-group-buttons {
            display: flex;
            justify-content: space-between;
            margin-bottom: 15px;
        }

        .input-group-buttons button {
            width: 48%;
            padding: 10px;
            background-color: rgba(0,20,96,0.8);
            color: white;
            border: none;
            border-radius: 4px;
            cursor: pointer;
            font-size: 16px;
            transition: background-color 0.3s ease;
            box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);
            font-family: 'Open Sans', sans-serif;
            font-weight: 600;
        }

        .input-group-buttons button:hover {
            background-color: #16206a;
        }

        .message {
            margin-top: 20px;
            padding: 10px;
            border-radius: 4px;
            display: none;
        }

        .message.success {
            background-color: #d4edda;
            color: #155724;
        }

        .message.error {
            background-color: #f8d7da;
            color: #721c24;
        }

        .verify-next {
            display: none;
            text-align: center;
            margin-top: 20px;
        }

        .verify-next button {
            padding: 10px 20px;
            background-color: rgba(0,20,96,0.8);
            color: white;
            border: none;
            border-radius: 4px;
            cursor: pointer;
            font-size: 16px;
            transition: background-color 0.3s ease;
            box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);
            font-family: 'Open Sans', sans-serif;
            font-weight: 600;
        }

        .verify-next button:hover {
            background-color: #16206a;
        }

        .spacer {
            height: 20px;
        }

        .loader {
            border: 4px solid #f3f3f3;
            border-radius: 50%;
            border-top: 4px solid #1b2781;
            width: 30px;
            height: 30px;
            animation: spin 2s linear infinite;
            display: none;
            margin: 0 auto;
        }

        @keyframes spin {
            0% { transform: rotate(0deg); }
            100% { transform: rotate(360deg); }
        }

        @media (max-width: 768px) {
            .container {
                width: 90%;
                max-width: 90%;
            }

            .input-group-buttons {
                flex-direction: column;
            }

            .input-group-buttons button {
                width: 100%;
                margin-bottom: 10px;
            }

            .verify-next button {
                width: 100%;
            }
        }

        @media (max-width: 480px) {
            .top-bar {
                font-size: 20px;
                padding: 10px;
            }

            .input-group input {
                width: calc(100% - 8px);
            }

            .input-group label {
                font-size: 14px;
            }

            .input-group-buttons button {
                font-size: 14px;
                padding: 8px;
            }

            .verify-next button {
                font-size: 14px;
                padding: 8px;
            }
        }
    </style>
</head>
<body>
    <div class="header">Partner Dining Usecase</div>
    <div class="container">
        <div class="top-bar">London Cafe Access</div>
        <div class="content">
            <div class="input-group" id="employeeIdGroup">
                <label for="employeeId">Employee ID</label>
                <input type="text" id="employeeId" placeholder="Enter Employee ID">
                <br/>
                <br/>
            </div>
            
            <div class="input-group input-group-buttons" id="buttonsGroup">
                <button onclick="enterAsHost()">Enter as Host</button>
                <button onclick="enterAsGuest()">Enter as Guest</button>
            </div>
            <div id="message" class="message"></div>
            <div class="loader" id="loader"></div>
            <br/>
            <br/>
            <div id="employeeDetails" class="input-group" style="display: none;">
                <label for="employeeName">Employee Name</label>
                <input type="text" id="employeeName" readonly>
            </div>
            <div id="employeeDepartment" class="input-group" style="display: none;">
                <label for="employeeDept">Department</label>
                <input type="text" id="employeeDept" readonly>
            </div>
            <div id="employeePosition" class="input-group" style="display: none;">
                <label for="employeePos">Position</label>
                <input type="text" id="employeePos" readonly>
            </div>
            <div class="spacer"></div>
            <div class="verify-next" id="verifyNextDiv">
                <button onclick="resetForm()">Verify Next Person</button>
            </div>
        </div>
    </div>

    <script>
        function enterAsGuest() {
            const employeeId = sanitizeInput(document.getElementById('employeeId').value);
            const messageDiv = document.getElementById('message');
            const loader = document.getElementById('loader');
            const employeeDetailsDiv = document.getElementById('employeeDetails');
            const employeeDepartmentDiv = document.getElementById('employeeDepartment');
            const employeePositionDiv = document.getElementById('employeePosition');
            const employeeNameInput = document.getElementById('employeeName');
            const employeeDeptInput = document.getElementById('employeeDept');
            const employeePosInput = document.getElementById('employeePos');
            const employeeIdGroup = document.getElementById('employeeIdGroup');
            const buttonsGroup = document.getElementById('buttonsGroup');

            // Hide input field and buttons
            employeeIdGroup.style.display = 'none';
            buttonsGroup.style.display = 'none';

            // Clear previous messages and details
            messageDiv.style.display = 'none';
            employeeDetailsDiv.style.display = 'none';
            employeeDepartmentDiv.style.display = 'none';
            employeePositionDiv.style.display = 'none';
            messageDiv.classList.remove('success', 'error');

            if (employeeId.trim() === "") {
                messageDiv.textContent = 'Please enter a valid Employee ID';
                messageDiv.classList.add('error');
                messageDiv.style.display = 'block';
                showVerifyNextButton();
                return;
            }

            // Show loader
            loader.style.display = 'block';

            // Simulate a database check (replace with actual API call)
            fetchEmployeeDetails(employeeId, function(employee) {
                // Hide loader
                loader.style.display = 'none';

                if (!employee) {
                    messageDiv.textContent = 'Please enter valid Employee ID';
                    messageDiv.classList.add('error');
                    messageDiv.style.display = 'block';
                } else {
                    employeeNameInput.value = employee.name;
                    employeeDeptInput.value = employee.department;
                    employeePosInput.value = employee.position;
                    employeeDetailsDiv.style.display = 'block';
                    employeeDepartmentDiv.style.display = 'block';
                    employeePositionDiv.style.display = 'block';
                    messageDiv.textContent = 'Cafeteria access has been granted';
                    messageDiv.classList.add('success');
                    messageDiv.style.display = 'block';
                }

                showVerifyNextButton();
            });
        }

        function enterAsHost() {
            const employeeId = sanitizeInput(document.getElementById('employeeId').value);
            const messageDiv = document.getElementById('message');
            const loader = document.getElementById('loader');
            const employeeDetailsDiv = document.getElementById('employeeDetails');
            const employeeDepartmentDiv = document.getElementById('employeeDepartment');
            const employeePositionDiv = document.getElementById('employeePosition');
            const employeeNameInput = document.getElementById('employeeName');
            const employeeDeptInput = document.getElementById('employeeDept');
            const employeePosInput = document.getElementById('employeePos');
            const employeeIdGroup = document.getElementById('employeeIdGroup');
            const buttonsGroup = document.getElementById('buttonsGroup');

            // Hide input field and buttons
            employeeIdGroup.style.display = 'none';
            buttonsGroup.style.display = 'none';

            // Clear previous messages and details
            messageDiv.style.display = 'none';
            employeeDetailsDiv.style.display = 'none';
            employeeDepartmentDiv.style.display = 'none';
            employeePositionDiv.style.display = 'none';
            messageDiv.classList.remove('success', 'error');

            if (employeeId.trim() === "") {
                messageDiv.textContent = 'Please enter a valid Employee ID';
                messageDiv.classList.add('error');
                messageDiv.style.display = 'block';
                showVerifyNextButton();
                return;
            }

            // Show loader
            loader.style.display = 'block';

            // Simulate a database check (replace with actual API call)
            fetchEmployeeDetails(employeeId, function(employee) {
                // Hide loader
                loader.style.display = 'none';

                if (!employee) {
                    messageDiv.textContent = 'Please enter valid Employee ID';
                    messageDiv.classList.add('error');
                    messageDiv.style.display = 'block';
                } else if (!employee.hasAccess) {
                    messageDiv.textContent = 'Access Denied';
                    messageDiv.classList.add('error');
                    messageDiv.style.display = 'block';
                } else {
                    employeeNameInput.value = employee.name;
                    employeeDeptInput.value = employee.department;
                    employeePosInput.value = employee.position;
                    employeeDetailsDiv.style.display = 'block';
                    employeeDepartmentDiv.style.display = 'block';
                    employeePositionDiv.style.display = 'block';
                    messageDiv.textContent = 'Access Granted';
                    messageDiv.classList.add('success');
                    messageDiv.style.display = 'block';
                }

                showVerifyNextButton();
            });
        }

        function showVerifyNextButton() {
            const verifyNextDiv = document.getElementById('verifyNextDiv');
            verifyNextDiv.style.display = 'block';
        }

        function resetForm() {
            document.getElementById('employeeId').value = '';
            document.getElementById('employeeName').value = '';
            document.getElementById('employeeDept').value = '';
            document.getElementById('employeePos').value = '';
            document.getElementById('message').style.display = 'none';
            document.getElementById('employeeDetails').style.display = 'none';
            document.getElementById('employeeDepartment').style.display = 'none';
            document.getElementById('employeePosition').style.display = 'none';
            document.getElementById('verifyNextDiv').style.display = 'none';
            document.getElementById('employeeIdGroup').style.display = 'block';
            document.getElementById('buttonsGroup').style.display = 'flex';
        }

        function sanitizeInput(input) {
            const div = document.createElement('div');
            div.textContent = input;
            return div.innerHTML;
        }

        function fetchEmployeeDetails(employeeId, callback) {
            // Replace this with an actual API call
            const employees = [
                { id: '123', name: 'John Doe', department: 'Sales', position: 'Manager', hasAccess: true },
                { id: '456', name: 'Jane Smith', department: 'Marketing', position: 'Executive', hasAccess: false },
                { id: '789', name: 'Guest User', department: 'HR', position: 'Assistant', hasAccess: true }
            ];
            
            const employee = employees.find(emp => emp.id === employeeId);
            setTimeout(() => callback(employee), 1000); // Simulate async API call
        }
    </script>
</body>
</html>
