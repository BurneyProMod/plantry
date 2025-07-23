// plantry/src/app.js
async function loadRecipes() {
  const res = await fetch("http://backend:5000/recipes");
  const list = await res.json();
  // render checkboxes…
}

async function generatePlan() {
  const selected = /* collect checked IDs */;
  const target  = /* parse serving input */;
  const res = await fetch("http://backend:5000/plan", {
    method: "POST",
    headers: {'Content-Type':'application/json'},
    body: JSON.stringify({ selected_ids: selected, target_servings: target })
  });
  const data = await res.json();
  // render plan & shopping list…
}

window.onload = () => {
  loadRecipes();
  document.getElementById("generate").onclick = generatePlan;
};
