#let margin = (x: 4mm, y: 2mm) // The printer prints from 0.45mm to the top and bottom edges
#let gutter = 3.5mm
#let cols-cnt = 3
// Font sizes: headings of 3 levels and numbers at their start, main text, code
#let font-sizes = (h1: 17pt, h2: 13pt, h3: 11pt, num1: 12pt, num2: 10pt, num3: 9pt, text: 7pt, code: 7pt, math-block: 9pt)
// Inline formula is this times bigger than the text around it: its small variables (x, n) are as high as small letters of Georgia
#let math-inline-scale = 1.08
// Background of the inline code and of every second line of the code block
#let code-fill = rgb("#EEEEEE")

#import "@preview/codly:2.0.0" as codly
// Border of code blocks, of line numbers and of the cpp label
#let code-stroke = 0.45pt + rgb("#777777")
#let code-radius = 3pt

// Border of a code block: the sides are on every part, the top and the bottom with round corners only at the
// real start and end of the block, so an unfinished part is open
#let code-cap(at-top, y: top) = {
  let r = code-radius
  let w = code-stroke.thickness
  let s = 0.6pt + w // Covers the square corner of the sides and of the fill
  let k = 0.5523 // Control points of a cubic curve that is a quarter of a circle
  let sy = if at-top { 1 } else { -1 }
  let corner(sx) = {
    let p(x, y) = (sx * (x - w / 2), sy * y) // The middle of the side
    place(top + left, curve(fill: white,
      curve.move(p(-s, -s)), curve.line(p(r, -s)), curve.line(p(r, 0pt)),
      curve.cubic(p(r - k * r, 0pt), p(0pt, r - k * r), p(0pt, r)),
      curve.line(p(-s, r)), curve.close()))
    place(top + left, curve(stroke: code-stroke,
      curve.move(p(r, 0pt)), curve.cubic(p(r - k * r, 0pt), p(0pt, r - k * r), p(0pt, r))))
  }
  place(y + left, box(width: 100%, height: 0pt, {
    place(top + left, corner(1))
    place(top + right, box(width: 0pt, corner(-1)))
    place(top + left, dx: r - w / 2, line(length: 100% - 2 * r + w, stroke: code-stroke))
  }))
}
// The sides are the gray fill around the white block with the code. The corners are drawn twice: here over the
// sides and in the header and the footer of codly over the lines, codly cuts them at its border
#let code-frame(body) = block(breakable: true, width: 100%, inset: (x: code-stroke.thickness),
  fill: code-stroke.paint, {
    code-cap(true)
    block(breakable: true, width: 100%, fill: white, body)
    code-cap(false, y: bottom)
  })

// Line break that leaves the real newline outside, so the next line can start with "="
#let br = raw("\n")

// l and ll at the end of long double functions and __builtin_*ll: bold
#let bold-l(body) = {
  show regex("\\b(__builtin_\\w+ll|(sqrt|cbrt|fabs|pow|exp|log|log2|log10|sin|cos|tan|asin|acos|atan|atan2|hypot|floor|ceil|round|fmod)l)\\b"): it => {
    let t = it.text
    let k = if t.starts-with("__builtin") { 2 } else { 1 }
    [#t.slice(0, t.len() - k)#strong(t.slice(t.len() - k))]
  }
  body
}

// Inline code: does not change the line height
#let code(str) = box(
  radius: 3pt,
  inset: (x: 2pt),
  outset: (y: 1.8pt),
  fill: code-fill,
  text(font: "Courier New", size: font-sizes.code, bold-l(str))
)

// Long table cut into `parts` tables standing in a row, each one repeats the header
#let split-table(parts, header, ..cells) = {
  let rows = cells.pos().chunks(header.len())
  align(center, grid(
    columns: parts,
    column-gutter: 1.5pt,
    ..rows.chunks(calc.ceil(rows.len() / parts)).map(part => table(
      columns: header.len(),
      ..header.map(strong),
      ..part.flatten()
    ))
  ))
}

#let setup(body) = {
  set page(
    paper: "a4",
    flipped: true, // Альбомная ориентация
    margin: margin, // Узкие поля для экономии места
    columns: cols-cnt,
  
    background: align(top,
      layout(size => {
        // Вычисляем полезную ширину текста
        let width = size.width - 2 * margin.x
        // Ширина одной колонки
        let col-width = (width - (cols-cnt - 1) * gutter) / cols-cnt
      
        // Настройки линии: серая, пунктирная (dashed) или точечная (dotted)
        let line-style = (paint: rgb("#888888"), thickness: 0.5pt, dash: (15pt, 7pt))
      
        // Координаты Y (от верхнего поля до нижнего)
        let y-start = 0pt
        let y-end = size.height
      
        // Рисуем первую линию
        let x1 = margin.x + col-width + gutter / 2
        place(top + left, line(start: (x1, y-start), end: (x1, y-end), stroke: line-style))
        // Рисуем вторую линию
        let x2 = x1 + col-width + gutter
        place(top + left, line(start: (x2, y-start), end: (x2, y-end), stroke: line-style))
      }),
    ),

  
    // Page number in all 4 corners, so it is seen when most of the page is covered.
    // It overlaps the text a bit, so it has a white outline.
    // The distance to the paper edges is the one of the first version: it is tested to be printable
    foreground: context {
      set text(font: "Times New Roman", size: font-sizes.h3, top-edge: "cap-height", bottom-edge: "baseline")
      let num = counter(page).display()
      for corner in (top + left, top + right, bottom + left, bottom + right) {
        place(
          corner,
          dx: if corner.x == left { margin.x } else { -margin.x },
          dy: if corner.y == top { 1.5mm } else { -1.5mm },
          {
            place(text(fill: black.transparentize(30%), stroke: 3pt + white.transparentize(30%), num))
            num
          }
        )
      }
    }
  )
  set columns(gutter: gutter) // Устанавливаем gutter между колонками
  set text(
    // Digits are from Gelasio (fonts/): in Georgia they have different heights
    font: ((name: "Gelasio", covers: regex("[0-9]")), "Georgia"), number-type: "lining", slashed-zero: true,
    size: font-sizes.text
  )
  set par(leading: 2.5pt)
  // A hyphen that is a separate word is a dash
  show regex("^-$"): "—"
  // Headings stay in the line, the line break after them comes from TeamBook.typ
  show heading: it => {
    // The number at the start: smaller thin italic, a bit lighter than black. The font is in fonts/
    show regex("^\\d+(\\.\\d+)*\\."): n => strong(delta: -300, text(font: "Old Standard TT", style: "italic",
      size: font-sizes.at("num" + str(it.depth)), slashed-zero: false, fill: rgb("#4d4d4d"), n))
    text(size: font-sizes.at("h" + str(it.depth)), weight: "regular", it.body)
  }
  // Math
  show math.equation.where(block: true): set text(size: font-sizes.math-block)
  show math.equation.where(block: false): set text(size: math-inline-scale * 1em)
  // Block formulas: wider space after a comma between formulas, but not inside brackets and indices: f(i, j), c_(i, j)
  show math.equation.where(block: true): it => {
    let gap = h(10pt)
    show ",": math.class("punctuation", ",") + gap
    show math.lr: it => { show h.where(amount: 10pt): none; it }
    show math.attach: it => { show h.where(amount: 10pt): none; it }
    it
  }
  // The same gap above and under a formula, between two formulas it is smaller
  show math.equation.where(block: true): set block(
    above: 5pt,
    below: -5.5pt
  )
  set table(inset: 3pt, stroke: 0.5pt)
  show table: set block(
    above: 8pt,
    below: -5pt
  )

  // Code
  show raw.where(block: true): it => code-frame(codly.new(it))
  show: codly.set_(
    radius: 0pt, // The border is drawn by code-frame
    leading: 0.07em,
    number-enabled: false, // Line numbers are a gutter column: it has a line on the right
    gutters: (codly.gutter-column(
      values: row => if row.kind == "code" { str(row.number) },
      fill: (white, code-fill), // Inverse of the line
      align: right + horizon, // Digits stay under each other: 9 and 10
      inset: (left: 1.5pt, right: 1.2pt, y: 1.07pt)
    ), codly.gutter-column( // The line after the numbers: a filled column hides its own stroke
      values: row => none, width: 0pt, inset: 0pt, fill: none, stroke: (left: code-stroke)
    )),
    header: code-cap(true), // Not repeated on breaks
    footer: code-cap(false),
    indent-guides: (width: 4, color: luma(40%).transparentize(40%), thickness: 0.3pt)
  )
  show: codly.header-set_(repeat: false, inset: 0pt, fill: none, stroke: none)
  show: codly.footer-set_(repeat: false, inset: 0pt, fill: none, stroke: none)
  show: codly.line-set_(fill: (code-fill, white), stroke: none, inset: (x: 1pt, y: 1.07pt))
  // The label hangs from the top border, not bound to the first line
  show: codly.lang-set_(default-color: black, fill: white.transparentize(30%), stroke: code-stroke, inset: (x: 1.5pt, y: 1.2pt),
    radius: 1.5pt, align: right + top, outset: (x: -1.2pt, y: 0pt))
  set raw(theme: "BW.tmTheme", tab-size: 4)
  show raw: it => {
    show "—": "-" // Not in code
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
    set block(spacing: 5pt, below: -2.5pt) // below + height of the text line after the code = gap under the code
    show text: set text(font: "Courier New") // All text is Courier New
    if it.lang == none { // Styled text
      block(it.text)
      return
    }
    show text: set text(size: font-sizes.code)
    set text(tracking: -0.12pt) // Tighter letters: 2 more symbols fit in a line
    show text.where(fill: rgb("#505050")): set text(font: "Caveat", size: 9.5pt) // Comments, the font is in fonts/
    bold-l(it)
  }

  body
}
