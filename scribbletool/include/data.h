constexpr char IndexHtml[] = R"(<!doctype html>
<html lang="en">
    <head>
        <title>{TITLE}</title>
        
        <meta charset="utf-8" />
        <meta
            name="viewport"
            content="width=device-width, initial-scale=1, shrink-to-fit=no"
        />

        <link
            href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.2/dist/css/bootstrap.min.css"
            rel="stylesheet"
        />
    </head>

    <body>
        <header class="container mt-3 mb-3">
            <h1>{TITLE}</h1>
        </header>
 
        <main>
            <div class="container">
                <div class="input-group mb-3">
                    <select id="search_criteria" class="form-select">
                        <option value="name">Name</option>
                        <option value="category">Category</option>
                        <option value="subcategories">Subcategory</option>
                        <option value="id">Object ID</option>
                        <option value="fileid">File ID</option>
                        <option value="triggers">Trigger</option>
                        <option value="actions">Action</option>
                    </select>
                    <input type="text" id="search_input" class="form-control" placeholder="Search...">
                </div>
        
                <ul id="entry_list" class="list-group">
                    {OBJ-ENTRIES}
                </ul>
            </div>
        </main>

        <footer class="container mt-3">
            
        </footer>
        
        <script src="search.js"></script>
        <script
            src="https://cdn.jsdelivr.net/npm/@popperjs/core@2.11.8/dist/umd/popper.min.js"
            integrity="sha384-I7E8VVD/ismYTF4hNIPjVp/Zjvgyol6VFvRkX/vR+Vc4jQkC+hVqc2pM8ODewa9r"
            crossorigin="anonymous"
        ></script>
        <script
            src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.2/dist/js/bootstrap.min.js"
            integrity="sha384-BBtl+eGJRgqQAUMxJ7pMwbEyER4l1g+O15P+16Ep7Q9Q+zqX6gSbd85u4mG4QzX+"
            crossorigin="anonymous"
        ></script>
    </body>
</html>
)";
constexpr char SearchJs[] = R"(document.getElementById("search_input").addEventListener("input", function() {
    let filter = this.value.toLowerCase();
    let criteria = document.getElementById("search_criteria").value;
    let items = document.querySelectorAll("#entry_list li");

    items.forEach(item => {
        let text = item.getAttribute("data-" + criteria).toLowerCase();
        item.style.display = text.includes(filter) ? "" : "none";
    });
});
)";
constexpr char ObjectHtml[] = R"(<!doctype html>
<html lang="en">
    <head>
        <title>Object: {OBJ-NAME}</title>
        
        <meta charset="utf-8" />
        <meta
            name="viewport"
            content="width=device-width, initial-scale=1, shrink-to-fit=no"
        />

        <link
            href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.2/dist/css/bootstrap.min.css"
            rel="stylesheet"
        />
    </head>

    <body>
        <header class="container mt-3 mb-3 d-flex">
            <h1>{OBJ-NAME}</h1>
            <button class="btn btn-info ms-auto" onclick="window.history.back();">
                ← Back
            </button>
        </header>

        <main>
            {OBJ-CONTENT}
        </main>

        <footer class="container mt-3">
        </footer>

        <script
            src="https://cdn.jsdelivr.net/npm/@popperjs/core@2.11.8/dist/umd/popper.min.js"
        ></script>
        <script
            src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.2/dist/js/bootstrap.min.js"
        ></script>
    </body>
</html>
)";
