#let margin = 5mm
#let gutter = 5mm
#let cols-cnt = 3
// Font sizes: headings of 3 levels, main text, code
#let font-sizes = (h1: 17pt, h2: 13pt, h3: 11pt, text: 9pt, code: 7pt)
// Background of the inline code and of every second line of the code block
#let code-fill = rgb("#EEEEEE")

#import "@preview/codly:1.3.0": *
#import "@preview/codly-languages:0.1.1": *

// Line break that leaves the real newline outside, so the next line can start with "="
#let br = raw("\n")

// Inline code: does not change the line height
#let code(str) = box(
  radius: 3pt,
  inset: (x: 3pt),
  outset: (y: 3pt),
  fill: code-fill,
  text(font: "Courier New", size: font-sizes.code, str)
)

#let setup(body) = {
  set page(
    paper: "a4",
    flipped: true, // Альбомная ориентация
    margin: margin, // Узкие поля для экономии места
    columns: cols-cnt,
  
    background: align(top,
      layout(size => {
        // Вычисляем полезную ширину текста
        let width = size.width - 2 * margin
        // Ширина одной колонки
        let col-width = (width - (cols-cnt - 1) * gutter) / cols-cnt
      
        // Настройки линии: черная, пунктирная (dashed) или точечная (dotted)
        let line-style = (paint: black, thickness: 1pt, dash: (15pt, 7pt))
      
        // Координаты Y (от верхнего поля до нижнего)
        let y-start = 0pt
        let y-end = size.height
      
        // Рисуем первую линию
        let x1 = margin + col-width + gutter / 2
        place(top + left, line(start: (x1, y-start), end: (x1, y-end), stroke: line-style))
        // Рисуем вторую линию
        let x2 = x1 + col-width + gutter
        place(top + left, line(start: (x2, y-start), end: (x2, y-end), stroke: line-style))
      }),
    ),

  
    footer: context[
      #set align(right)
      #set text(
        font: "Times New Roman",
        size: font-sizes.h3
      )
      #move(dy: -4mm, block(
        fill: white,
        inset: (x: 3pt, y: 2pt),
        radius: 4pt,
        counter(page).display("1", both: false)
      ))
    ]
  )
  set columns(gutter: gutter) // Устанавливаем gutter между колонками
  set text(
    font: "Georgia",
    size: font-sizes.text
  )
  // Headings stay in the line, the line break after them comes from TeamBook.typ
  show heading: it => text(size: font-sizes.at("h" + str(it.depth)), weight: "regular", it.body)
  // Math
  show math.equation.where(block: true): set block(
    above: 8pt,
    below: -5pt
  )
  show table: set block(
    above: 8pt,
    below: -5pt
  )

  // Code
  show: codly-init.with()
  codly(
    radius: 3pt,
    zebra-fill: code-fill,
    default-color: rgb("#FFFFFF"),
    lang-stroke: 0.5pt + rgb("#AAAAAA"),
    lang-inset: 1.3pt,
    lang-outset: (x: 1pt, y: 0pt),
    inset: 1.2pt
  )
  set raw(theme: "BW.tmTheme", tab-size: 4)
  show raw: it => {
    if it.text.trim() == "" { // Spaces and enters
      text(
        font: "Times New Roman",
        size: font-sizes.text,
        it
      )
      return
    }
    // Code
    set par(leading: 0.35em)
    set block(below: -1pt)
    show text: set text(font: "Courier New") // All text is Courier New
    if it.lang == none { // Styled text
      block(it.text)
      return
    }
    show text: set text(size: font-sizes.code)
    show text.where(fill: rgb("#666666")): set text(font: "Times New Roman") // Comments
    it
  }

  body
}
