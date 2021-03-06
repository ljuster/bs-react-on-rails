type component('props, 'context) =
  (Js.t({..} as 'props), Js.t({..} as 'context)) => ReasonReact.reactElement;

type options = {traceTurbolinks: bool};

type optionsJs = {. "traceTurbolinks": bool};

type reactOnRails('props, 'context) = {
  .
  "register": [@bs.meth] (Js.Dict.t(component('props, 'context)) => unit),
  "setOptions": [@bs.meth] (optionsJs => unit),
  "authenticityToken": [@bs.meth] (unit => Js.nullable(string)),
  "reactOnRailsPageLoaded": [@bs.meth] (unit => unit),
};

[@bs.module "react-on-rails"]
external reactOnRails : reactOnRails('props, 'context) = "default";

let register = (name: string, component: component('props, 'context)) =>
  reactOnRails##register([(name, component)] |> Js.Dict.fromList);

let mapOptionsToJs = (options: options) : optionsJs => {
  "traceTurbolinks": options.traceTurbolinks,
};

let registerWithOptions =
    (name: string, component: component('props, 'context), options: options) => {
  reactOnRails##setOptions(options |> mapOptionsToJs);
  register(name, component);
};

let reactOnRailsPageLoaded = () => reactOnRails##reactOnRailsPageLoaded();

let authenticityToken = () =>
  reactOnRails##authenticityToken() |> Js.Nullable.toOption;

type defaultContext = {
  .
  "host": string,
  "href": string,
  "httpAcceptLanguage": string,
  "i18nDefaultLocale": string,
  "i18nLocale": string,
  "inMailer": bool,
  "location": string,
  "pathname": string,
  "port": int,
  "scheme": string,
  "search": Js.nullable(string),
  "serverSide": bool,
};
