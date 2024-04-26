// The project function defines how your document looks.
// It takes your content and some metadata and formats it.
// Go ahead and customize it to your liking!
#let project(university: "", department: "", title: "", subtitle: "", authors: (), date: none, body) = {
  // Set the document's basic properties.
  set document(author: authors.map(a => a.name), title: title)
  set page(numbering: "1", number-align: center)
  set text(font: "Linux Libertine", lang: "pt")
  set heading(numbering: "1.1")
  show math.equation: set text(weight: 400)

  // Title row.
  align(center + horizon)[
    #block(text(weight: 500, 1.2em, university))
    #block(text(weight: 500, 1.1em, department))
    \
    \
    #block(text(weight: 700, 1.75em, title))
    #block(text(weight: 500, 1.25em, subtitle))
    #v(1em, weak: true)
    #date
    \
    \
  ]

  // Author information.
  pad(
    top: 0.5em,
    bottom: 0.5em,
    x: 2em,
    grid(
      columns: (1fr,) * calc.min(1, authors.len()),
      gutter: 1em,
      ..authors.map(author => align(center)[
        *#author.name* \
        #author.number
      ]),
    ),
  )

  // Main body.
  set par(justify: true)

  // indent lists
  set list(indent: 8pt)

  body
}