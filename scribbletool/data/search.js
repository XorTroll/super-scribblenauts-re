document.getElementById("search_input").addEventListener("input", function() {
    let filter = this.value.toLowerCase();
    let criteria = document.getElementById("search_criteria").value;
    let items = document.querySelectorAll("#entry_list li");

    items.forEach(item => {
        let text = item.getAttribute("data-" + criteria).toLowerCase();
        item.style.display = text.includes(filter) ? "" : "none";
    });
});
