const documents = [
    {
        name: "cpp.txt",
        content: "C++ is a powerful programming language used for software development."
    },
    {
        name: "dsa.txt",
        content: "Data Structures and Algorithms include arrays, linked lists, trees and graphs."
    },
    {
        name: "cloud.txt",
        content: "Cloud computing provides scalable computing resources over the internet."
    },
    {
        name: "dbms.txt",
        content: "Database Management Systems store, retrieve and manage data efficiently."
    },
    {
        name: "networking.txt",
        content: "Computer networking connects devices using protocols like TCP/IP."
    },
    {
        name: "os.txt",
        content: "Operating systems manage hardware resources and processes."
    }
];

let totalSearches = 0;

const searchInput = document.getElementById("searchInput");
const searchBtn = document.getElementById("searchBtn");
const results = document.getElementById("results");
const suggestions = document.getElementById("suggestions");
const stats = document.getElementById("stats");

function updateStats() {
    stats.innerHTML = `
        <p><strong>Indexed Documents:</strong> ${documents.length}</p>
        <p><strong>Total Searches:</strong> ${totalSearches}</p>
    `;
}

function searchDocuments() {

    const query = searchInput.value.toLowerCase().trim();

    if(query === "")
        return;

    totalSearches++;

    let html = "";

    documents.forEach(doc => {

        if(doc.content.toLowerCase().includes(query)) {

            html += `
            <div class="result-card">
                <h3>${doc.name}</h3>
                <p>${doc.content}</p>
            </div>
            `;
        }

    });

    if(html === "")
        html = "<p>No matching documents found.</p>";

    results.innerHTML = html;

    updateStats();
}

function autocomplete() {

    const query = searchInput.value.toLowerCase();

    suggestions.innerHTML = "";

    if(query.length === 0)
        return;

    const words = [
        "cloud",
        "cloud computing",
        "cpp",
        "class",
        "database",
        "data structure",
        "network",
        "operating system",
        "algorithm"
    ];

    words.forEach(word => {

        if(word.startsWith(query)) {

            const div = document.createElement("div");

            div.innerText = word;

            div.onclick = function() {

                searchInput.value = word;

                suggestions.innerHTML = "";

                searchDocuments();
            };

            suggestions.appendChild(div);
        }

    });

}

searchBtn.addEventListener("click", searchDocuments);

searchInput.addEventListener("keyup", autocomplete);

updateStats();