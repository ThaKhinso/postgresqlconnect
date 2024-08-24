document.getElementById('loginForm').addEventListener('submit', function(event) {
    event.preventDefault();  // Prevent the form from submitting the traditional way

    // Gather the form data
    const username = document.getElementById('username').value;
    const password = document.getElementById('password').value;

    // Create the JSON payload
    const loginData = {
        username: username,
        password: password
    };

    // Send the JSON data to the server
    fetch('/sigin', {  // Replace '/login' with your server's endpoint
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify(loginData)
    })
    .then(response => response.text())
.then(html => {
    document.body.innerHTML = html;
})
    // .then(response => response.json())  // Assuming the server responds with JSON
    // .then(data => {
    //     // Handle the response from the server
    //     if (data.success) {
    //         alert('Login successful!');
    //         // Redirect or take other action
    //     } else {
    //         alert('Login failed: ' + data.message);
    //     }
    // })
    .catch(error => console.error('Error:', error));
});
